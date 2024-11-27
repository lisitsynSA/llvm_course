
// Generated from Expression.g4 by ANTLR 4.9.2


#include "ExpressionListener.h"
#include "ExpressionVisitor.h"

#include "ExpressionParser.h"


using namespace antlrcpp;
using namespace antlr4;

ExpressionParser::ExpressionParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ExpressionParser::~ExpressionParser() {
  delete _interpreter;
}

std::string ExpressionParser::getGrammarFileName() const {
  return "Expression.g4";
}

const std::vector<std::string>& ExpressionParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ExpressionParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ExprContext ------------------------------------------------------------------

ExpressionParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ExpressionParser::ExprContext *> ExpressionParser::ExprContext::expr() {
  return getRuleContexts<ExpressionParser::ExprContext>();
}

ExpressionParser::ExprContext* ExpressionParser::ExprContext::expr(size_t i) {
  return getRuleContext<ExpressionParser::ExprContext>(i);
}

tree::TerminalNode* ExpressionParser::ExprContext::INT() {
  return getToken(ExpressionParser::INT, 0);
}


size_t ExpressionParser::ExprContext::getRuleIndex() const {
  return ExpressionParser::RuleExpr;
}

void ExpressionParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExpressionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void ExpressionParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ExpressionListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


antlrcpp::Any ExpressionParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ExpressionVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}


ExpressionParser::ExprContext* ExpressionParser::expr() {
   return expr(0);
}

ExpressionParser::ExprContext* ExpressionParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ExpressionParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  ExpressionParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 0;
  enterRecursionRule(_localctx, 0, ExpressionParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(10);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ExpressionParser::T__0: {
        setState(3);
        match(ExpressionParser::T__0);
        setState(4);
        expr(5);
        break;
      }

      case ExpressionParser::T__4: {
        setState(5);
        match(ExpressionParser::T__4);
        setState(6);
        expr(0);
        setState(7);
        match(ExpressionParser::T__5);
        break;
      }

      case ExpressionParser::INT: {
        setState(9);
        match(ExpressionParser::INT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(20);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(18);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(12);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(13);
          _la = _input->LA(1);
          if (!(_la == ExpressionParser::T__1

          || _la == ExpressionParser::T__2)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(14);
          expr(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(15);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(16);
          _la = _input->LA(1);
          if (!(_la == ExpressionParser::T__0

          || _la == ExpressionParser::T__3)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(17);
          expr(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(22);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool ExpressionParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 0: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ExpressionParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> ExpressionParser::_decisionToDFA;
atn::PredictionContextCache ExpressionParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ExpressionParser::_atn;
std::vector<uint16_t> ExpressionParser::_serializedATN;

std::vector<std::string> ExpressionParser::_ruleNames = {
  "expr"
};

std::vector<std::string> ExpressionParser::_literalNames = {
  "", "'-'", "'*'", "'/'", "'+'", "'{'", "'}'"
};

std::vector<std::string> ExpressionParser::_symbolicNames = {
  "", "", "", "", "", "", "", "INT", "WS"
};

dfa::Vocabulary ExpressionParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ExpressionParser::_tokenNames;

ExpressionParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0xa, 0x1a, 0x4, 0x2, 0x9, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 
       0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0xd, 
       0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 
       0x2, 0x7, 0x2, 0x15, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x18, 0xb, 0x2, 
       0x3, 0x2, 0x2, 0x3, 0x2, 0x3, 0x2, 0x2, 0x4, 0x3, 0x2, 0x4, 0x5, 
       0x4, 0x2, 0x3, 0x3, 0x6, 0x6, 0x2, 0x1c, 0x2, 0xc, 0x3, 0x2, 0x2, 
       0x2, 0x4, 0x5, 0x8, 0x2, 0x1, 0x2, 0x5, 0x6, 0x7, 0x3, 0x2, 0x2, 
       0x6, 0xd, 0x5, 0x2, 0x2, 0x7, 0x7, 0x8, 0x7, 0x7, 0x2, 0x2, 0x8, 
       0x9, 0x5, 0x2, 0x2, 0x2, 0x9, 0xa, 0x7, 0x8, 0x2, 0x2, 0xa, 0xd, 
       0x3, 0x2, 0x2, 0x2, 0xb, 0xd, 0x7, 0x9, 0x2, 0x2, 0xc, 0x4, 0x3, 
       0x2, 0x2, 0x2, 0xc, 0x7, 0x3, 0x2, 0x2, 0x2, 0xc, 0xb, 0x3, 0x2, 
       0x2, 0x2, 0xd, 0x16, 0x3, 0x2, 0x2, 0x2, 0xe, 0xf, 0xc, 0x6, 0x2, 
       0x2, 0xf, 0x10, 0x9, 0x2, 0x2, 0x2, 0x10, 0x15, 0x5, 0x2, 0x2, 0x7, 
       0x11, 0x12, 0xc, 0x5, 0x2, 0x2, 0x12, 0x13, 0x9, 0x3, 0x2, 0x2, 0x13, 
       0x15, 0x5, 0x2, 0x2, 0x6, 0x14, 0xe, 0x3, 0x2, 0x2, 0x2, 0x14, 0x11, 
       0x3, 0x2, 0x2, 0x2, 0x15, 0x18, 0x3, 0x2, 0x2, 0x2, 0x16, 0x14, 0x3, 
       0x2, 0x2, 0x2, 0x16, 0x17, 0x3, 0x2, 0x2, 0x2, 0x17, 0x3, 0x3, 0x2, 
       0x2, 0x2, 0x18, 0x16, 0x3, 0x2, 0x2, 0x2, 0x5, 0xc, 0x14, 0x16, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ExpressionParser::Initializer ExpressionParser::_init;
