#include "ExpressionLexer.h"
#include "ExpressionParser.h"
#include "ExpressionVisitor.h"
#include "antlr4-runtime.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include <any>
#include <iostream>
using namespace llvm;

struct TreeLLVMWalker : public ExpressionVisitor {
  IRBuilder<> *builder;
  TreeLLVMWalker(IRBuilder<> *builder) : builder(builder) {}
  antlrcpp::Any visitExpr(ExpressionParser::ExprContext *ctx) override {
    // INT
    if (ctx->INT()) {
      return (Value *)builder->getInt32(std::stoi(ctx->INT()->getText()));
    }
    // '-' expr
    if (ctx->children.size() == 2) {
      return builder->CreateNeg(visitExpr(ctx->expr()[0]).as<Value *>());
    }
    // '{' expr '}'
    if (ctx->children[0]->getText().at(0) == '{') {
      return visit(ctx->children[1]);
    }
    // expr ( '*' | '/') expr
    // expr ( '+' | '-') expr
    Value *lhs = visit(ctx->children[0]).as<Value *>();
    Value *rhs = visit(ctx->children[2]).as<Value *>();
    switch (ctx->children[1]->getText().at(0)) {
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
};

struct TreeDumpWalker : public ExpressionVisitor {
  std::string Tab;
  antlrcpp::Any visitExpr(ExpressionParser::ExprContext *ctx) override {
    Tab += "\t";
    int res = 0;
    // INT
    if (ctx->INT()) {
      res = std::stoi(ctx->INT()->getText());
      outs() << Tab << res << "\n";
    }
    // '-' expr
    if (ctx->children.size() == 2) {
      outs() << Tab << "neg\n";
      res = -visitExpr(ctx->expr()[0]).as<int>();
    }
    if (ctx->children.size() == 3) {
      // '{' expr '}'
      if (ctx->children[0]->getText().at(0) == '{') {
        outs() << Tab << "{ }\n";
        res = visit(ctx->children[1]);
      } else {
        // expr ( '*' | '/') expr
        // expr ( '+' | '-') expr
        int lhs = visit(ctx->children[0]).as<int>();
        outs() << Tab << ctx->children[1]->getText() << "\n";
        int rhs = visit(ctx->children[2]).as<int>();
        switch (ctx->children[1]->getText().at(0)) {
        case '*':
          res = lhs * rhs;
          break;
        case '/':
          res = lhs / rhs;
          break;
        case '+':
          res = lhs + rhs;
          break;
        case '-':
          res = lhs - rhs;
          break;
        default:
          outs() << "Error\n";
          return nullptr;
        }
      }
    }
    Tab.pop_back();
    return res;
  }
};

struct TreeWalker : public ExpressionVisitor {
  antlrcpp::Any visitExpr(ExpressionParser::ExprContext *ctx) override {
    // INT
    if (ctx->INT()) {
      return std::stoi(ctx->INT()->getText());
    }
    // '-' expr
    if (ctx->children.size() == 2) {
      return -visitExpr(ctx->expr()[0]).as<int>();
    }
    // '{' expr '}'
    if (ctx->children[0]->getText().at(0) == '{') {
      return visit(ctx->children[1]);
    }
    // expr ( '*' | '/') expr
    // expr ( '+' | '-') expr
    int lhs = visit(ctx->children[0]).as<int>();
    int rhs = visit(ctx->children[2]).as<int>();
    switch (ctx->children[1]->getText().at(0)) {
    case '*':
      return lhs * rhs;
    case '/':
      return lhs / rhs;
    case '+':
      return lhs + rhs;
    case '-':
      return lhs - rhs;
    default:
      break;
    }
    return nullptr;
  }
};

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    outs() << "[ERROR] Need 1 argument: file with expression\n";
    return 1;
  }
  // Open file
  std::ifstream stream;
  stream.open(argv[1]);

  // Provide the input text in a stream
  antlr4::ANTLRInputStream input(stream);

  // Create a lexer from the input
  ExpressionLexer lexer(&input);

  // Create a token stream from the lexer
  antlr4::CommonTokenStream tokens(&lexer);

  // Create a parser from the token stream
  ExpressionParser parser(&tokens);

  // Display the parse tree
  // outs() << parser.expr()->toStringTree() << "\n";
  // return 0;

  // Associate a visitor with the Expr context
  //TreeWalker walker;
  //TreeDumpWalker walker;
  //int res = walker.visitExpr(parser.expr()).as<int>();
  //outs() << "Visitor output: " << res << "\n";
  //return 0;

  LLVMContext context;
  Module *module = new Module("top", context);
  IRBuilder<> builder(context);

  // declare void @main()
  FunctionType *funcType = FunctionType::get(builder.getInt32Ty(), false);
  Function *mainFunc =
      Function::Create(funcType, Function::ExternalLinkage, "main", module);
  // entry:
  BasicBlock *entryBB = BasicBlock::Create(context, "entry", mainFunc);

  builder.SetInsertPoint(entryBB);
  TreeLLVMWalker walker(&builder);
  builder.CreateRet(walker.visitExpr(parser.expr()).as<Value *>());

  outs() << "[LLVM IR]\n";
  module->print(outs(), nullptr);
  outs() << "\n";
  bool verif = verifyFunction(*mainFunc, &outs());
  outs() << "[VERIFICATION] " << (!verif ? "OK\n\n" : "FAIL\n\n");

  return 0;
}