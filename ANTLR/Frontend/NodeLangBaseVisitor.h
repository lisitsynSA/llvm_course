
// Generated from NodeLang.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "NodeLangVisitor.h"


/**
 * This class provides an empty implementation of NodeLangVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  NodeLangBaseVisitor : public NodeLangVisitor {
public:

  virtual antlrcpp::Any visitProgram(NodeLangParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNodeDecl(NodeLangParser::NodeDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncDecl(NodeLangParser::FuncDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNode(NodeLangParser::NodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarDecl(NodeLangParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr(NodeLangParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

