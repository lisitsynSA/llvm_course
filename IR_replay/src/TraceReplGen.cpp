#include "../include/TraceReplGen.h"

using namespace llvm;

bool TraceReplayGenerator::loadOriginalModule(const std::string &llPath) {
  SMDiagnostic Err;
  OriginalModule = parseIRFile(llPath, Err, Context);
  if (!OriginalModule) {
    Err.print("TraceReplayGenerator", errs());
    return false;
  }

  // Сохраняем типы функций
  for (auto &F : *OriginalModule) {
    FuncNameToType[F.getName().str()] = F.getFunctionType();
  }

  return true;
}

void TraceReplayGenerator::populateMocks(const std::vector<CallEvent> &calls) {
  CallSequence = &calls;

  for (const auto &ev : calls) {
    if (ev.is_external || ev.func_name == "main") {
      outs() << "  populateMocks for " << ev.func_name << '\n';
      MockReturns[ev.func_name].push_back(ev.return_value);
      MockArgs[ev.func_name].push_back(ev.args);
    }
  }
}

Function *TraceReplayGenerator::createMockFunction(const std::string &Name,
                                                   FunctionType *FT) {
  outs() << "  createMockFunction for " << Name << '\n';
  Function *Mock = nullptr;
  if (Name == "main") {
    Mock = Function::Create(FT, GlobalValue::ExternalLinkage, Name + "_mock",
                            OriginalModule.get());

  } else {
    Mock = Function::Create(FT, GlobalValue::InternalLinkage, Name + "_mock",
                            OriginalModule.get());
  }

  BasicBlock *Entry = BasicBlock::Create(Context, "entry", Mock);
  IRBuilder<> Builder(Entry);

  auto &RealArgs = MockArgs[Name];
  auto args_val = RealArgs.front();
  RealArgs.erase(RealArgs.begin());
  uint32_t i = 0;
  std::vector<Value *> Args;
  for (auto &Arg : Mock->args()) {
    Args.push_back(createValueFromBits(Builder, Arg.getType(), args_val[i]));
    i++;
  }

  // Вызов реальной внешней функции
  Function *RealFunc = OriginalModule->getFunction(Name);
  if (RealFunc) { // && Name == "main") {
    Builder.CreateCall(RealFunc, Args);
  }

  auto &returns = MockReturns[Name];
  if (returns.empty()) {
    Builder.CreateUnreachable();
    return Mock;
  }

  uint64_t ret_val = returns.front();
  returns.erase(returns.begin());

  Value *RetVal = createValueFromBits(Builder, FT->getReturnType(), ret_val);
  Builder.CreateRet(RetVal);

  return Mock;
}

Value *TraceReplayGenerator::createValueFromBits(IRBuilder<> &Builder, Type *Ty,
                                                 uint64_t bits) {
  if (Ty->isIntegerTy()) {
    unsigned width = Ty->getIntegerBitWidth();
    return ConstantInt::get(Context, APInt(width, bits, true));
  }
  if (Ty->isPointerTy()) {
    Value *IntVal = ConstantInt::get(Type::getInt64Ty(Context), bits);
    return Builder.CreateIntToPtr(IntVal, Ty);
  }
  if (Ty->isFloatTy()) {
    float f;
    memcpy(&f, &bits, sizeof(float));
    return ConstantFP::get(Ty, f);
  }
  if (Ty->isDoubleTy()) {
    double d;
    memcpy(&d, &bits, sizeof(d));
    return ConstantFP::get(Ty, d);
  }
  return Constant::getNullValue(Ty);
}

bool TraceReplayGenerator::generate() {
  // === 2. Создаём моки для внешних функций ===
  outs() << "[3] Mock functions creation...\n";
  for (auto &F : *OriginalModule) {
    if (F.isDeclaration()) {
      createMockFunction(F.getName().str(), F.getFunctionType());
    }
  }

  // === 3. Копируем функции, кроме main → переименуем в original_main ===
  outs() << "[2] Functions copying...\n";
  for (auto &F : *OriginalModule) {
    // if (F.isDeclaration())
    //   continue;

    Function *NewFunc = nullptr;
    if (F.getName() == "main") {
      createMockFunction(F.getName().str(), F.getFunctionType());
      F.setName("original_main");
    }
    for (auto &BB : F) {
      for (auto &I : BB) {
        if (auto *Call = dyn_cast<CallInst>(&I)) {
          Function *Callee = Call->getCalledFunction();
          if (Callee && Callee->isDeclaration()) {
            // Заменяем на мок
            Function *Mock =
                OriginalModule->getFunction(Callee->getName().str() + "_mock");
            if (Mock) {
              Call->setCalledFunction(Mock);
            }
          }
        }
      }
    }
  }
  Function *NewMain = OriginalModule->getFunction("main_mock");
  if (NewMain) {
    NewMain->setName("main");
  }

  if (verifyModule(*OriginalModule, &errs())) {
    errs() << "Replay module verification failed!\n";
    return true;
    return false;
  }

  return true;
}

void TraceReplayGenerator::saveToFile(const std::string &outputPath) {
  std::error_code EC;
  raw_fd_ostream OS(outputPath, EC);
  if (EC) {
    errs() << "Cannot open output file: " << EC.message() << '\n';
    return;
  }
  OriginalModule->print(OS, nullptr);
  OS.close();
}