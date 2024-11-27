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
#include <any>
#include <iostream>
using namespace llvm;

struct TreeLLVMWalker : public NodeLangVisitor {
  std::vector<std::map<std::string, Value *>> vars;
  Function *currFunc;
  LLVMContext *ctxLLVM;
  Module *module;
  IRBuilder<> *builder;
  Type *voidType;
  Type *int32Type;
  TreeLLVMWalker(LLVMContext *ctxLLVM, IRBuilder<> *builder, Module *module)
      : ctxLLVM(ctxLLVM), builder(builder), module(module) {
    voidType = Type::getVoidTy(*ctxLLVM);
    int32Type = Type::getInt32Ty(*ctxLLVM);
  }

  antlrcpp::Any visitProgram(NodeLangParser::ProgramContext *ctx) override {
    outs() << "visitProgram\n";
    // declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef)
    ArrayRef<Type *> simPutPixelParamTypes = {int32Type, int32Type, int32Type};
    FunctionType *simPutPixelType =
        FunctionType::get(int32Type, simPutPixelParamTypes, false);
    module->getOrInsertFunction("PUT_PIXEL", simPutPixelType);

    // declare void @simFlush(...)
    FunctionType *simFlushType = FunctionType::get(int32Type, false);
    module->getOrInsertFunction("FLUSH", simFlushType);

    vars.push_back(
        std::map<std::string, Value *>{{"SIM_Y_SIZE", builder->getInt32(256)},
                                       {"SIM_X_SIZE", builder->getInt32(512)}});
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
    outs() << "visitFuncDecl: " << name << "\n";
    vars.push_back({});

    std::vector<Type *> funcParamTypes;
    for (int arg = 1; arg < ctx->ID().size(); arg++) {
      funcParamTypes.push_back(int32Type);
    }
    FunctionType *funcType =
        FunctionType::get(int32Type, funcParamTypes, false);
    Function *func = Function::Create(funcType, Function::ExternalLinkage,
                                      ctx->ID()[0]->getText(), module);
    BasicBlock *entryBB = BasicBlock::Create(*ctxLLVM, "entry", func);
    builder->SetInsertPoint(entryBB);
    currFunc = func;

    for (int arg = 1; arg < ctx->ID().size(); arg++) {
      registerVar(ctx->ID()[arg]->getText(), func->getArg(arg - 1));
    }

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
    vars.push_back({});
    if (ctx->node().size() < 3) {
      outs() << "[Error] Too few arguments for LOOP\n";
      return nullptr;
    }
    Value *beg = visitNode(ctx->node()[1]).as<Value *>();
    Value *end = visitNode(ctx->node()[2]).as<Value *>();

    BasicBlock *prev = builder->GetInsertBlock();
    BasicBlock *cmpBB = BasicBlock::Create(*ctxLLVM, "", currFunc);
    BasicBlock *iterationBB = BasicBlock::Create(*ctxLLVM, "", currFunc);
    BasicBlock *exitBB = BasicBlock::Create(*ctxLLVM, "", currFunc);

    builder->CreateBr(cmpBB);
    builder->SetInsertPoint(cmpBB);
    PHINode *it = builder->CreatePHI(builder->getInt32Ty(), 2);
    it->addIncoming(beg, prev);
    registerVar(ctx->node()[0]->getText(), it);
    auto cond = builder->CreateICmpEQ(it, end);
    builder->CreateCondBr(cond, exitBB, iterationBB);
    builder->SetInsertPoint(iterationBB);

    for (int i = 3; i < ctx->node().size(); i++) {
      visitNode(ctx->node()[i]);
    }

    Value *inc = builder->CreateAdd(it, builder->getInt32(1));
    builder->CreateBr(cmpBB);
    it->addIncoming(inc, builder->GetInsertBlock());
    builder->SetInsertPoint(exitBB);

    vars.pop_back();
    return (Value *)it;
  }

  antlrcpp::Any visitFuncCall(std::string &name,
                              NodeLangParser::NodeContext *ctx) {
    outs() << "visitFuncCall: " << name << "\n";
    // node: ... | '{' FuncID node* '}'
    Function *func = module->getFunction(name);
    if (!func) {
      outs() << "[Error] Unknown Function name: " << name << "\n";
      return nullptr;
    }
    int argSize = ctx->node().size();
    if (argSize != func->arg_size()) {
      outs() << "[Error] Wrong arguments number for " << name << "\n";
      return nullptr;
    }
    std::vector<Value *> args;
    for (int i = 0; i < argSize; i++) {
      args.push_back(visitNode(ctx->node()[i]));
    }
    return (Value *)builder->CreateCall(func, args);
  }

  antlrcpp::Any visitVarDecl(NodeLangParser::VarDeclContext *ctx) override {
    // varDecl: ID expr;
    std::string name = ctx->ID()->getText();
    outs() << "visitVarDecl: " << name << "\n";
    return registerVar(name, visitExpr(ctx->expr()).as<Value *>());
  }

  antlrcpp::Any visitExpr(NodeLangParser::ExprContext *ctx) override {
    outs() << "visitExpr\n";
    // ID
    if (ctx->ID()) {
      return searchVar(ctx->ID()->getText());
    }
    // INT
    if (ctx->INT()) {
      return (Value *)builder->getInt32(std::stoi(ctx->INT()->getText()));
    }
    // '-' expr
    if (ctx->children.size() == 2) {
      return builder->CreateNeg(visit(ctx->children[1]).as<Value *>());
    }
    // '(' expr ')'
    if (ctx->children[0]->getText().at(0) == '(') {
      return visit(ctx->children[1]);
    }
    // ( '*' | '/') expr expr
    // ( '+' | '-') expr expr
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
      break;
    }
    return nullptr;
  }

  Value *registerVar(const std::string &name, Value *val) {
    outs() << "registerVar: " << name << "\n";
    vars.back()[name] = val;
    return val;
  }

  Value *searchVar(const std::string &name) {
    outs() << "searchVar: " << name << "\n";
    for (auto it = vars.rbegin(); it != vars.rend(); ++it) {
      if (auto find = it->find(name); find != it->end()) {
        return find->second;
      }
    }
    Function *func = module->getFunction(name);
    if (!func || func->arg_size() > 0) {
      outs() << "[Error] Can't find variable: " << name << "\n";
      return nullptr;
    }
    outs() << "Change to FuncCall: " << name << "\n";
    return (Value *)builder->CreateCall(func);
  }
};

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    outs() << "[ERROR] Need 1 argument: file with NodeLang\n";
    return 1;
  }
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
  // outs() << parser.program()->toStringTree() << "\n";
  // return 0;

  LLVMContext context;
  Module *module = new Module("top", context);
  IRBuilder<> builder(context);

  TreeLLVMWalker walker(&context, &builder, module);
  walker.visitProgram(parser.program());

  outs() << "[LLVM IR]\n";
  module->print(outs(), nullptr);
  outs() << "\n";
  bool verif = verifyModule(*module, &outs());
  outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");

  Function *appFunc = module->getFunction("app");
  if (appFunc == nullptr) {
    outs() << "Can't find app function\n";
    return -1;
  }

  // LLVM IR Interpreter
  outs() << "[EE] Run\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> void * {
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

  return 0;
}