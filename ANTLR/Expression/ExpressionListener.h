
// Generated from Expression.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "ExpressionParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by ExpressionParser.
 */
class  ExpressionListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterExpr(ExpressionParser::ExprContext *ctx) = 0;
  virtual void exitExpr(ExpressionParser::ExprContext *ctx) = 0;


};

