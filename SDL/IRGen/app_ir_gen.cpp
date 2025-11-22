#include "../sim.h"

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

int main() {
  LLVMContext context;
  // ; ModuleID = 'app.c'
  // source_filename = "app.c"
  Module *module = new Module("app.c", context);
  IRBuilder<> builder(context);

  // declare void @simPutPixel(i32, i32, i32)
  // local_unnamed_addr #1
  Type *voidType = Type::getVoidTy(context);
  Type *int32Type = Type::getInt32Ty(context);
  ArrayRef<Type *> simPutPixelParamTypes = {int32Type, int32Type, int32Type};
  FunctionType *simPutPixelType =
      FunctionType::get(voidType, simPutPixelParamTypes, false);
  FunctionCallee simPutPixelFunc =
      module->getOrInsertFunction("simPutPixel", simPutPixelType);

  // declare void @simFlush()
  FunctionType *simFlushType = FunctionType::get(voidType, false);
  FunctionCallee simFlushFunc =
      module->getOrInsertFunction("simFlush", simFlushType);

  // define void @app() {
  FunctionType *appFuncType = FunctionType::get(voidType, false);
  Function *appFunc =
      Function::Create(appFuncType, Function::ExternalLinkage, "app", module);

  // BasicBlocks:
  BasicBlock *BB0 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB1 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB3 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB4 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB7 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB10 = BasicBlock::Create(context, "", appFunc);
  BasicBlock *BB13 = BasicBlock::Create(context, "", appFunc);

  // 0:
  builder.SetInsertPoint(BB0);
  // br label %1
  builder.CreateBr(BB1);

  // 3:                                                ; preds = %7
  builder.SetInsertPoint(BB3);
  // ret void
  builder.CreateRetVoid();

  // 1:                                                ; preds = %0, %7
  builder.SetInsertPoint(BB1);
  // %2 = phi i32 [ 0, %0 ], [ %8, %7 ]
  PHINode *val2 = builder.CreatePHI(int32Type, 2);
  // br label %4
  builder.CreateBr(BB4);

  // 4:                                                ; preds = %1, %10
  builder.SetInsertPoint(BB4);
  // %5 = phi i32 [ 0, %1 ], [ %11, %10 ]
  PHINode *val5 = builder.CreatePHI(int32Type, 2);
  // %6 = mul nuw nsw i32 %5, %2
  Value *val6 = builder.CreateMul(val5, val2, "", true, true);
  // br label %13
  builder.CreateBr(BB13);

  // 7:                                                ; preds = %10
  builder.SetInsertPoint(BB7);
  // call void @simFlush()
  builder.CreateCall(simFlushFunc);
  // %8 = add nuw nsw i32 %2, 1
  Value *val8 = builder.CreateAdd(val2, builder.getInt32(1), "", true, true);
  // %9 = icmp eq i32 %8, 1000
  Value *val9 = builder.CreateICmpEQ(val8, builder.getInt32(1000));
  // br i1 %9, label %3, label %1, !llvm.loop !5
  builder.CreateCondBr(val9, BB3, BB1);

  // 10:                                               ; preds = %13
  builder.SetInsertPoint(BB10);
  // %11 = add nuw nsw i32 %5, 1
  Value *val11 = builder.CreateAdd(val5, builder.getInt32(1), "", true, true);
  // %12 = icmp eq i32 %11, 256
  Value *val12 = builder.CreateICmpEQ(val11, builder.getInt32(SIM_Y_SIZE));
  // br i1 %12, label %7, label %4, !llvm.loop !7
  builder.CreateCondBr(val12, BB7, BB4);

  // 13:                                               ; preds = %4, %13
  builder.SetInsertPoint(BB13);
  // %14 = phi i32 [ 0, %4 ], [ %17, %13 ]
  PHINode *val14 = builder.CreatePHI(int32Type, 2);
  // %15 = mul nuw nsw i32 %6, %14
  Value *val15 = builder.CreateMul(val6, val14, "", true, true);
  // %16 = add nsw i32 %15, -16777216
  Value *val16 = builder.CreateNSWAdd(val15, builder.getInt32(-16777216));
  // call void @simPutPixel(i32 %14, i32 %5, i32 %16)
  Value *args[] = {val14, val5, val16};
  builder.CreateCall(simPutPixelFunc, args);
  // %17 = add nuw nsw i32 %14, 1
  Value *val17 = builder.CreateAdd(val14, builder.getInt32(1), "", true, true);
  // %18 = icmp eq i32 %17, 512
  Value *val18 = builder.CreateICmpEQ(val17, builder.getInt32(SIM_X_SIZE));
  // br i1 %18, label %10, label %13, !llvm.loop !8
  builder.CreateCondBr(val18, BB10, BB13);
  // }

  // Link PHI nodes
  // %2 = phi i32 [ 0, %0 ], [ %8, %7 ]
  val2->addIncoming(builder.getInt32(0), BB0);
  val2->addIncoming(val8, BB7);
  // %5 = phi i32 [ 0, %1 ], [ %11, %10 ]
  val5->addIncoming(builder.getInt32(0), BB1);
  val5->addIncoming(val11, BB10);
  // %14 = phi i32 [ 0, %4 ], [ %17, %13 ]
  val14->addIncoming(builder.getInt32(0), BB4);
  val14->addIncoming(val17, BB13);

  // Dump LLVM IR
  module->print(outs(), nullptr);
  outs() << '\n';
  bool verif = verifyModule(*module, &outs());
  outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");

  // LLVM IR Interpreter
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([](const std::string &fnName) -> void * {
    if (fnName == "simPutPixel") {
      return reinterpret_cast<void *>(simPutPixel);
    }
    if (fnName == "simFlush") {
      return reinterpret_cast<void *>(simFlush);
    }
    outs() << "[ExecutionEngine] Can't find function " << fnName
           << ". Catch the Segmentation fault:)\n";
    return nullptr;
  });
  ee->finalizeObject();

  simInit();

  ArrayRef<GenericValue> noargs;
  GenericValue v = ee->runFunction(appFunc, noargs);
  outs() << "[EE] Result: " << v.IntVal << '\n';

  simExit();
  return EXIT_SUCCESS;
}
