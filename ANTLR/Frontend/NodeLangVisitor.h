
// Generated from NodeLang.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "NodeLangParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by NodeLangParser.
 */
class  NodeLangVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by NodeLangParser.
   */
    virtual antlrcpp::Any visitProgram(NodeLangParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitNodeDecl(NodeLangParser::NodeDeclContext *context) = 0;

    virtual antlrcpp::Any visitFuncDecl(NodeLangParser::FuncDeclContext *context) = 0;

    virtual antlrcpp::Any visitNode(NodeLangParser::NodeContext *context) = 0;

    virtual antlrcpp::Any visitVarDecl(NodeLangParser::VarDeclContext *context) = 0;

    virtual antlrcpp::Any visitExpr(NodeLangParser::ExprContext *context) = 0;


};

