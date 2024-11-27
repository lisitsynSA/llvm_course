
// Generated from NodeLang.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "NodeLangListener.h"


/**
 * This class provides an empty implementation of NodeLangListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  NodeLangBaseListener : public NodeLangListener {
public:

  virtual void enterProgram(NodeLangParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(NodeLangParser::ProgramContext * /*ctx*/) override { }

  virtual void enterNodeDecl(NodeLangParser::NodeDeclContext * /*ctx*/) override { }
  virtual void exitNodeDecl(NodeLangParser::NodeDeclContext * /*ctx*/) override { }

  virtual void enterFuncDecl(NodeLangParser::FuncDeclContext * /*ctx*/) override { }
  virtual void exitFuncDecl(NodeLangParser::FuncDeclContext * /*ctx*/) override { }

  virtual void enterNode(NodeLangParser::NodeContext * /*ctx*/) override { }
  virtual void exitNode(NodeLangParser::NodeContext * /*ctx*/) override { }

  virtual void enterVarDecl(NodeLangParser::VarDeclContext * /*ctx*/) override { }
  virtual void exitVarDecl(NodeLangParser::VarDeclContext * /*ctx*/) override { }

  virtual void enterExpr(NodeLangParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(NodeLangParser::ExprContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

