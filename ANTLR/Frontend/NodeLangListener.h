
// Generated from NodeLang.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "NodeLangParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by NodeLangParser.
 */
class  NodeLangListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(NodeLangParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(NodeLangParser::ProgramContext *ctx) = 0;

  virtual void enterNodeDecl(NodeLangParser::NodeDeclContext *ctx) = 0;
  virtual void exitNodeDecl(NodeLangParser::NodeDeclContext *ctx) = 0;

  virtual void enterFuncDecl(NodeLangParser::FuncDeclContext *ctx) = 0;
  virtual void exitFuncDecl(NodeLangParser::FuncDeclContext *ctx) = 0;

  virtual void enterNode(NodeLangParser::NodeContext *ctx) = 0;
  virtual void exitNode(NodeLangParser::NodeContext *ctx) = 0;

  virtual void enterVarDecl(NodeLangParser::VarDeclContext *ctx) = 0;
  virtual void exitVarDecl(NodeLangParser::VarDeclContext *ctx) = 0;

  virtual void enterExpr(NodeLangParser::ExprContext *ctx) = 0;
  virtual void exitExpr(NodeLangParser::ExprContext *ctx) = 0;


};

