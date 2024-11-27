
// Generated from Expression.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "ExpressionVisitor.h"


/**
 * This class provides an empty implementation of ExpressionVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ExpressionBaseVisitor : public ExpressionVisitor {
public:

  virtual antlrcpp::Any visitExpr(ExpressionParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

