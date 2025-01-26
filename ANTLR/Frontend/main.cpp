#include "../../SDL/sim.h"
#include "NodeLangLexer.h"
#include "NodeLangParser.h"
#include "NodeLangVisitor.h"
#include "antlr4-runtime.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <cstddef>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace llvm;

struct TreeLLVMWalker : public NodeLangVisitor {
  std::vector<std::map<std::string, Value *>> vars;
  Function *currFunc;
  LLVMContext *ctxLLVM;
  Module *module;
  IRBuilder<> *builder;
  bool interpretMode;
  Type *int32Type;
  Type *voidType;
  TreeLLVMWalker(LLVMContext *ctxLLVM, IRBuilder<> *builder, Module *module,
                 bool interpretMode)
      : ctxLLVM(ctxLLVM), builder(builder), module(module),
        interpretMode(interpretMode) {
    int32Type = Type::getInt32Ty(*ctxLLVM);
    voidType = Type::getVoidTy(*ctxLLVM);
  }

  void regGraphicFuncs() {
    // declare i32 @PUT_PIXEL(i32, i32, i32)
    ArrayRef<Type *> simPutPixelParamTypes = {int32Type, int32Type, int32Type};
    FunctionType *simPutPixelType =
        FunctionType::get(int32Type, simPutPixelParamTypes, false);
    module->getOrInsertFunction("PUT_PIXEL", simPutPixelType);

    // declare i32 @FLUSH()
    FunctionType *simFlushType = FunctionType::get(int32Type, false);
    module->getOrInsertFunction("FLUSH", simFlushType);
  }

  void regGraphicFuncsIntr() {
    // declare void @llvm.sim.putpixel(i32 noundef, i32 noundef, i32 noundef)
    ArrayRef<Type *> simPutPixelParamTypes = {int32Type, int32Type, int32Type};
    FunctionType *simPutPixelIntrType =
        FunctionType::get(voidType, simPutPixelParamTypes, false);
    FunctionCallee simPutPixelIntr =
        module->getOrInsertFunction("llvm.sim.putpixel", simPutPixelIntrType);

    // define i32 @PUT_PIXEL(i32 %0, i32 %1, i32 %2) {
    FunctionType *simPutPixelType =
        FunctionType::get(int32Type, simPutPixelParamTypes, false);
    Function *simPutPixelFunc = Function::Create(
        simPutPixelType, Function::ExternalLinkage, "PUT_PIXEL", module);
    // entry:
    builder->SetInsertPoint(
        BasicBlock::Create(*ctxLLVM, "entry", simPutPixelFunc));
    // call void @llvm.sim.putpixel(i32 %0, i32 %1, i32 %2)
    builder->CreateCall(simPutPixelIntr,
                        {simPutPixelFunc->getArg(0), simPutPixelFunc->getArg(1),
                         simPutPixelFunc->getArg(2)});
    // ret i32 0
    builder->CreateRet(builder->getInt32(0));

    // declare void @llvm.sim.flush()
    FunctionType *simFlushIntrType = FunctionType::get(voidType, false);
    FunctionCallee simFlushIntr =
        module->getOrInsertFunction("llvm.sim.flush", simFlushIntrType);

    // define i32 @FLUSH() {
    FunctionType *simFlushType = FunctionType::get(int32Type, false);
    Function *simFlushFunc = Function::Create(
        simFlushType, Function::ExternalLinkage, "FLUSH", module);
    // entry:
    builder->SetInsertPoint(
        BasicBlock::Create(*ctxLLVM, "entry", simFlushFunc));
    // call void @llvm.sim.flush()
    builder->CreateCall(simFlushIntr);
    // ret i32 0
    builder->CreateRet(builder->getInt32(0));
  }

  antlrcpp::Any visitProgram(NodeLangParser::ProgramContext *ctx) override {
    outs() << "visitProgram\n";
    if (interpretMode) {
      regGraphicFuncs();
    } else {
      regGraphicFuncsIntr();
    }
    vars.push_back(
        std::map<std::string, Value *>{{"Y_SIZE", builder->getInt32(256)},
                                       {"X_SIZE", builder->getInt32(512)}});
    // program: nodeDecl+;
    for (auto it : ctx->nodeDecl()) {
      visitNodeDecl(it);
    }
    return nullptr;
  }

  antlrcpp::Any visitNodeDecl(NodeLangParser::NodeDeclContext *ctx) override {
    outs() << "visitNodeDecl\n";
    // nodeDecl: '(' 'NODE' (varDecl | funcDecl) ')';
    if (ctx->varDecl()) {
      return visitVarDecl(ctx->varDecl());
    }
    if (ctx->funcDecl()) {
      return visitFuncDecl(ctx->funcDecl());
    }
    return nullptr;
  }

  antlrcpp::Any visitFuncDecl(NodeLangParser::FuncDeclContext *ctx) override {
    // funcDecl: ID '(' ID* ')' node+;
    std::string name = ctx->ID()[0]->getText();
    outs() << "visitFuncDecl: " << name << '\n';
    vars.emplace_back();

    // (i32 %0, i32 %1, i32 %2)
    std::vector<Type *> funcParamTypes(ctx->ID().size() - 1, int32Type);

    // define i32 @color(i32 %0, i32 %1, i32 %2)
    FunctionType *funcType =
        FunctionType::get(int32Type, funcParamTypes, false);
    Function *func = Function::Create(funcType, Function::ExternalLinkage,
                                      ctx->ID()[0]->getText(), module);
    // entry:
    BasicBlock *entryBB = BasicBlock::Create(*ctxLLVM, "entry", func);
    builder->SetInsertPoint(entryBB);
    currFunc = func;

    // (x y step) -> (i32 %0, i32 %1, i32 %2)
    for (int arg = 1; arg < ctx->ID().size(); arg++) {
      registerVar(ctx->ID()[arg]->getText(), func->getArg(arg - 1));
    }

    // Add instructions
    Value *res = nullptr;
    for (auto it : ctx->node()) {
      res = visitNode(it).as<Value *>();
    }
    vars.pop_back();
    builder->CreateRet(res);
    return nullptr;
  }

  antlrcpp::Any visitNode(NodeLangParser::NodeContext *ctx) override {
    outs() << "visitNode\n";
    // node: nodeDecl | ... ;
    if (ctx->nodeDecl()) {
      return visitNodeDecl(ctx->nodeDecl());
    }
    if (ctx->expr()) {
      // node: ... | expr ;
      return visitExpr(ctx->expr());
    }
    // node: ... | '{' ID node* '}';
    if (ctx->ID()) {
      std::string name = ctx->ID()->getText();
      if (name == "LOOP") {
        // node: ... | '{' LOOP it begin end node* '}';
        return visitLoop(ctx);
      }
      // node: ... | '{' FuncID node* '}'
      return visitFuncCall(name, ctx);
    }
    return nullptr;
  }

  antlrcpp::Any visitLoop(NodeLangParser::NodeContext *ctx) {
    outs() << "visitLoop\n";
    // node: ... | '{' LOOP it begin end node* '}';
    vars.emplace_back();
    if (ctx->node().size() < 3) {
      outs() << "[Error] Too few arguments for LOOP\n";
      return nullptr;
    }
    Value *beg = visitNode(ctx->node()[1]).as<Value *>();
    Value *end = visitNode(ctx->node()[2]).as<Value *>();

    // br label cmpBB
    BasicBlock *prevBB = builder->GetInsertBlock();
    // it = phi i32 [ 0, prevBB ], [ inc, iterationBB ]
    // cond = icmp eq i32 %1, end
    // br i1 cond, exitBB, iterationBB
    BasicBlock *cmpBB = BasicBlock::Create(*ctxLLVM, "", currFunc);
    // inc = add i32 it, 1
    // br label cmpBB
    BasicBlock *iterationBB = BasicBlock::Create(*ctxLLVM, "", currFunc);
    // function continuation
    BasicBlock *exitBB = BasicBlock::Create(*ctxLLVM, "", currFunc);

    // br label cmpBB
    builder->CreateBr(cmpBB);
    builder->SetInsertPoint(cmpBB);
    // it = phi i32 [ 0, prevBB ], [ inc, iterationBB ]
    PHINode *it = builder->CreatePHI(builder->getInt32Ty(), 2);
    it->addIncoming(beg, prevBB);
    registerVar(ctx->node()[0]->getText(), it);
    // cond = icmp eq i32 %1, end
    auto cond = builder->CreateICmpEQ(it, end);
    // br i1 cond, exitBB, iterationBB
    builder->CreateCondBr(cond, exitBB, iterationBB);
    builder->SetInsertPoint(iterationBB);

    // Iteration code generation
    for (int i = 3; i < ctx->node().size(); i++) {
      visitNode(ctx->node()[i]);
    }

    // inc = add i32 it, 1
    Value *inc = builder->CreateAdd(it, builder->getInt32(1));
    // br label cmpBB
    builder->CreateBr(cmpBB);
    // it = phi i32 [ 0, prevBB ], [ inc, iterationBB ]
    it->addIncoming(inc, builder->GetInsertBlock());
    builder->SetInsertPoint(exitBB);

    vars.pop_back();
    return (Value *)it;
  }

  antlrcpp::Any visitFuncCall(std::string &name,
                              NodeLangParser::NodeContext *ctx) {
    // node: ... | '{' FuncID node* '}'
    outs() << "visitFuncCall: " << name << '\n';
    // i32 @color(i32 %0, i32 %1, i32 %2)
    Function *func = module->getFunction(name);
    if (!func) {
      outs() << "[Error] Unknown Function name: " << name << '\n';
      return nullptr;
    }
    int argSize = ctx->node().size();
    if (argSize != func->arg_size()) {
      outs() << "[Error] Wrong arguments number for " << name << '\n';
      return nullptr;
    }
    // (i32 %13, i32 %6, i32 %1)
    std::vector<Value *> args;
    args.reserve(argSize);
    for (int i = 0; i < argSize; i++) {
      args.push_back(visitNode(ctx->node()[i]));
    }
    // %16 = call i32 @color(i32 %13, i32 %6, i32 %1)
    return (Value *)builder->CreateCall(func, args);
  }

  antlrcpp::Any visitVarDecl(NodeLangParser::VarDeclContext *ctx) override {
    // varDecl: ID expr;
    std::string name = ctx->ID()->getText();
    outs() << "visitVarDecl: " << name << '\n';
    return registerVar(name, visitExpr(ctx->expr()).as<Value *>());
  }

  antlrcpp::Any visitExpr(NodeLangParser::ExprContext *ctx) override {
    outs() << "visitExpr: ";
    // ID
    if (ctx->ID()) {
      outs() << ctx->ID()->getText() << '\n';
      return searchVar(ctx->ID()->getText());
    }
    // INT
    if (ctx->INT()) {
      outs() << ctx->INT()->getText() << '\n';
      return (Value *)builder->getInt32(std::stoi(ctx->INT()->getText()));
    }
    // '-' expr
    if (ctx->children.size() == 2) {
      outs() << "neg\n";
      return builder->CreateNeg(visit(ctx->children[1]).as<Value *>());
    }
    // '(' expr ')'
    if (ctx->children[0]->getText().at(0) == '(') {
      outs() << "()\n";
      return visit(ctx->children[1]);
    }
    // ( '*' | '/') expr expr
    // ( '+' | '-') expr expr
    outs() << ctx->children[0]->getText() << '\n';
    Value *lhs = visit(ctx->children[1]).as<Value *>();
    Value *rhs = visit(ctx->children[2]).as<Value *>();
    switch (ctx->children[0]->getText().at(0)) {
    case '*':
      return builder->CreateMul(lhs, rhs);
    case '/':
      return builder->CreateSDiv(lhs, rhs);
    case '+':
      return builder->CreateAdd(lhs, rhs);
    case '-':
      return builder->CreateSub(lhs, rhs);
    default:
      return nullptr;
    }
  }

  Value *registerVar(const std::string &name, Value *val) {
    outs() << "registerVar: " << name << '\n';
    vars.back()[name] = val;
    return val;
  }

  Value *searchVar(const std::string &name) {
    outs() << "searchVar: " << name << '\n';
    for (auto it = vars.rbegin(); it != vars.rend(); ++it) {
      if (auto find = it->find(name); find != it->end()) {
        return find->second;
      }
    }
    // Conflict resolving: node: (expr) <-> (ID)
    Function *func = module->getFunction(name);
    if (!func || func->arg_size() > 0) {
      outs() << "[Error] Can't find variable: " << name << '\n';
      return nullptr;
    }
    outs() << "Change to FuncCall: " << name << '\n';
    return (Value *)builder->CreateCall(func);
  }
};

int main(int argc, const char *argv[]) {
  if (argc != 2 && argc != 3) {
    outs() << "[ERROR] Need arguments: file with NodeLang and optional output "
              "file for LLVM IR\n";
    return 1;
  }
  bool interpretMode = (argc == 2);
  // Open file
  std::ifstream stream;
  stream.open(argv[1]);

  // Provide the input text in a stream
  antlr4::ANTLRInputStream input(stream);

  // Create a lexer from the input
  NodeLangLexer lexer(&input);

  // Create a token stream from the lexer
  antlr4::CommonTokenStream tokens(&lexer);

  // Create a parser from the token stream
  NodeLangParser parser(&tokens);

  // Display the parse tree
  // outs() << parser.program()->toStringTree() << '\n';
  // return 0;

  LLVMContext context;
  Module *module = new Module("top", context);
  IRBuilder<> builder(context);

  TreeLLVMWalker walker(&context, &builder, module, interpretMode);
  walker.visitProgram(parser.program());

  outs() << "[LLVM IR]\n";
  module->print(outs(), nullptr);
  outs() << '\n';
  bool verif = verifyModule(*module, &outs());
  outs() << "[VERIFICATION] " << (verif ? "FAIL\n\n" : "OK\n\n");

  Function *appFunc = module->getFunction("app");
  if (appFunc == nullptr) {
    outs() << "Can't find app function\n";
    return -1;
  }

  if (interpretMode) {
    // LLVM IR Interpreter
    outs() << "[EE] Run\n";
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([](const std::string &fnName) -> void * {
    if (fnName == "PUT_PIXEL") {
      return reinterpret_cast<void *>(simPutPixel);
      }
      if (fnName == "FLUSH") {
        return reinterpret_cast<void *>(simFlush);
      }
      return nullptr;
    });
    ee->finalizeObject();

    simInit();

    ArrayRef<GenericValue> noargs;
    GenericValue v = ee->runFunction(appFunc, noargs);
    outs() << "[EE] Result: " << v.IntVal << "\n";

    simExit();
  } else {
    // Dump LLVM IR with intrinsics
    outs() << "[OUTPUT] " << argv[2] << "\n";
    std::error_code EC;
    raw_fd_ostream OutputFile(argv[2], EC);
    if (!EC) {
      module->print(OutputFile, nullptr);
    }
  }

  return 0;
}
