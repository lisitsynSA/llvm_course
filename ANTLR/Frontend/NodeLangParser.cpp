
// Generated from NodeLang.g4 by ANTLR 4.9.2


#include "NodeLangListener.h"
#include "NodeLangVisitor.h"

#include "NodeLangParser.h"


using namespace antlrcpp;
using namespace antlr4;

NodeLangParser::NodeLangParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

NodeLangParser::~NodeLangParser() {
  delete _interpreter;
}

std::string NodeLangParser::getGrammarFileName() const {
  return "NodeLang.g4";
}

const std::vector<std::string>& NodeLangParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& NodeLangParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

NodeLangParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<NodeLangParser::NodeDeclContext *> NodeLangParser::ProgramContext::nodeDecl() {
  return getRuleContexts<NodeLangParser::NodeDeclContext>();
}

NodeLangParser::NodeDeclContext* NodeLangParser::ProgramContext::nodeDecl(size_t i) {
  return getRuleContext<NodeLangParser::NodeDeclContext>(i);
}


size_t NodeLangParser::ProgramContext::getRuleIndex() const {
  return NodeLangParser::RuleProgram;
}

void NodeLangParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void NodeLangParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any NodeLangParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<NodeLangVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

NodeLangParser::ProgramContext* NodeLangParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, NodeLangParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(13);
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(12);
      nodeDecl();
      setState(15);
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == NodeLangParser::T__0);

  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NodeDeclContext ------------------------------------------------------------------

NodeLangParser::NodeDeclContext::NodeDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

NodeLangParser::VarDeclContext* NodeLangParser::NodeDeclContext::varDecl() {
  return getRuleContext<NodeLangParser::VarDeclContext>(0);
}

NodeLangParser::FuncDeclContext* NodeLangParser::NodeDeclContext::funcDecl() {
  return getRuleContext<NodeLangParser::FuncDeclContext>(0);
}


size_t NodeLangParser::NodeDeclContext::getRuleIndex() const {
  return NodeLangParser::RuleNodeDecl;
}

void NodeLangParser::NodeDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNodeDecl(this);
}

void NodeLangParser::NodeDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNodeDecl(this);
}


antlrcpp::Any NodeLangParser::NodeDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<NodeLangVisitor*>(visitor))
    return parserVisitor->visitNodeDecl(this);
  else
    return visitor->visitChildren(this);
}

NodeLangParser::NodeDeclContext* NodeLangParser::nodeDecl() {
  NodeDeclContext *_localctx = _tracker.createInstance<NodeDeclContext>(_ctx, getState());
  enterRule(_localctx, 2, NodeLangParser::RuleNodeDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(17);
    match(NodeLangParser::T__0);
    setState(18);
    match(NodeLangParser::T__1);
    setState(21);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(19);
      varDecl();
      break;
    }

    case 2: {
      setState(20);
      funcDecl();
      break;
    }

    default:
      break;
    }
    setState(23);
    match(NodeLangParser::T__2);

  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDeclContext ------------------------------------------------------------------

NodeLangParser::FuncDeclContext::FuncDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> NodeLangParser::FuncDeclContext::ID() {
  return getTokens(NodeLangParser::ID);
}

tree::TerminalNode* NodeLangParser::FuncDeclContext::ID(size_t i) {
  return getToken(NodeLangParser::ID, i);
}

std::vector<NodeLangParser::NodeContext *> NodeLangParser::FuncDeclContext::node() {
  return getRuleContexts<NodeLangParser::NodeContext>();
}

NodeLangParser::NodeContext* NodeLangParser::FuncDeclContext::node(size_t i) {
  return getRuleContext<NodeLangParser::NodeContext>(i);
}


size_t NodeLangParser::FuncDeclContext::getRuleIndex() const {
  return NodeLangParser::RuleFuncDecl;
}

void NodeLangParser::FuncDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDecl(this);
}

void NodeLangParser::FuncDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDecl(this);
}


antlrcpp::Any NodeLangParser::FuncDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<NodeLangVisitor*>(visitor))
    return parserVisitor->visitFuncDecl(this);
  else
    return visitor->visitChildren(this);
}

NodeLangParser::FuncDeclContext* NodeLangParser::funcDecl() {
  FuncDeclContext *_localctx = _tracker.createInstance<FuncDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, NodeLangParser::RuleFuncDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(25);
    match(NodeLangParser::ID);
    setState(26);
    match(NodeLangParser::T__0);
    setState(30);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == NodeLangParser::ID) {
      setState(27);
      match(NodeLangParser::ID);
      setState(32);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(33);
    match(NodeLangParser::T__2);
    setState(35);
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(34);
      node();
      setState(37);
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << NodeLangParser::T__0)
      | (1ULL << NodeLangParser::T__3)
      | (1ULL << NodeLangParser::T__4)
      | (1ULL << NodeLangParser::T__5)
      | (1ULL << NodeLangParser::T__6)
      | (1ULL << NodeLangParser::ID)
      | (1ULL << NodeLangParser::INT))) != 0));

  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NodeContext ------------------------------------------------------------------

NodeLangParser::NodeContext::NodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

NodeLangParser::NodeDeclContext* NodeLangParser::NodeContext::nodeDecl() {
  return getRuleContext<NodeLangParser::NodeDeclContext>(0);
}

NodeLangParser::ExprContext* NodeLangParser::NodeContext::expr() {
  return getRuleContext<NodeLangParser::ExprContext>(0);
}

tree::TerminalNode* NodeLangParser::NodeContext::ID() {
  return getToken(NodeLangParser::ID, 0);
}

std::vector<NodeLangParser::NodeContext *> NodeLangParser::NodeContext::node() {
  return getRuleContexts<NodeLangParser::NodeContext>();
}

NodeLangParser::NodeContext* NodeLangParser::NodeContext::node(size_t i) {
  return getRuleContext<NodeLangParser::NodeContext>(i);
}


size_t NodeLangParser::NodeContext::getRuleIndex() const {
  return NodeLangParser::RuleNode;
}

void NodeLangParser::NodeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNode(this);
}

void NodeLangParser::NodeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNode(this);
}


antlrcpp::Any NodeLangParser::NodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<NodeLangVisitor*>(visitor))
    return parserVisitor->visitNode(this);
  else
    return visitor->visitChildren(this);
}

NodeLangParser::NodeContext* NodeLangParser::node() {
  NodeContext *_localctx = _tracker.createInstance<NodeContext>(_ctx, getState());
  enterRule(_localctx, 6, NodeLangParser::RuleNode);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(50);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(39);
      nodeDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(40);
      expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(41);
      match(NodeLangParser::T__0);
      setState(42);
      match(NodeLangParser::ID);
      setState(46);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << NodeLangParser::T__0)
        | (1ULL << NodeLangParser::T__3)
        | (1ULL << NodeLangParser::T__4)
        | (1ULL << NodeLangParser::T__5)
        | (1ULL << NodeLangParser::T__6)
        | (1ULL << NodeLangParser::ID)
        | (1ULL << NodeLangParser::INT))) != 0)) {
        setState(43);
        node();
        setState(48);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(49);
      match(NodeLangParser::T__2);
      break;
    }

    default:
      break;
    }

  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

NodeLangParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* NodeLangParser::VarDeclContext::ID() {
  return getToken(NodeLangParser::ID, 0);
}

NodeLangParser::ExprContext* NodeLangParser::VarDeclContext::expr() {
  return getRuleContext<NodeLangParser::ExprContext>(0);
}


size_t NodeLangParser::VarDeclContext::getRuleIndex() const {
  return NodeLangParser::RuleVarDecl;
}

void NodeLangParser::VarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecl(this);
}

void NodeLangParser::VarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecl(this);
}


antlrcpp::Any NodeLangParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<NodeLangVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

NodeLangParser::VarDeclContext* NodeLangParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 8, NodeLangParser::RuleVarDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    match(NodeLangParser::ID);
    setState(53);
    expr();

  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

NodeLangParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<NodeLangParser::ExprContext *> NodeLangParser::ExprContext::expr() {
  return getRuleContexts<NodeLangParser::ExprContext>();
}

NodeLangParser::ExprContext* NodeLangParser::ExprContext::expr(size_t i) {
  return getRuleContext<NodeLangParser::ExprContext>(i);
}

tree::TerminalNode* NodeLangParser::ExprContext::INT() {
  return getToken(NodeLangParser::INT, 0);
}

tree::TerminalNode* NodeLangParser::ExprContext::ID() {
  return getToken(NodeLangParser::ID, 0);
}


size_t NodeLangParser::ExprContext::getRuleIndex() const {
  return NodeLangParser::RuleExpr;
}

void NodeLangParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void NodeLangParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<NodeLangListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}


antlrcpp::Any NodeLangParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<NodeLangVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

NodeLangParser::ExprContext* NodeLangParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 10, NodeLangParser::RuleExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(71);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(55);
      match(NodeLangParser::T__3);
      setState(56);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(57);
      _la = _input->LA(1);
      if (!(_la == NodeLangParser::T__4

      || _la == NodeLangParser::T__5)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(58);
      expr();
      setState(59);
      expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(61);
      _la = _input->LA(1);
      if (!(_la == NodeLangParser::T__3

      || _la == NodeLangParser::T__6)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(62);
      expr();
      setState(63);
      expr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(65);
      match(NodeLangParser::T__0);
      setState(66);
      expr();
      setState(67);
      match(NodeLangParser::T__2);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(69);
      match(NodeLangParser::INT);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(70);
      match(NodeLangParser::ID);
      break;
    }

    default:
      break;
    }

  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> NodeLangParser::_decisionToDFA;
atn::PredictionContextCache NodeLangParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN NodeLangParser::_atn;
std::vector<uint16_t> NodeLangParser::_serializedATN;

std::vector<std::string> NodeLangParser::_ruleNames = {
  "program", "nodeDecl", "funcDecl", "node", "varDecl", "expr"
};

std::vector<std::string> NodeLangParser::_literalNames = {
  "", "'('", "'NODE'", "')'", "'-'", "'*'", "'/'", "'+'"
};

std::vector<std::string> NodeLangParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "ID", "INT", "WS"
};

dfa::Vocabulary NodeLangParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> NodeLangParser::_tokenNames;

NodeLangParser::Initializer::Initializer() {
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
       0x3, 0xc, 0x4c, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4,
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9,
       0x7, 0x3, 0x2, 0x6, 0x2, 0x10, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x11,
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x18, 0xa, 0x3,
       0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x1f,
       0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x22, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4,
       0x6, 0x4, 0x26, 0xa, 0x4, 0xd, 0x4, 0xe, 0x4, 0x27, 0x3, 0x5, 0x3,
       0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x2f, 0xa, 0x5, 0xc,
       0x5, 0xe, 0x5, 0x32, 0xb, 0x5, 0x3, 0x5, 0x5, 0x5, 0x35, 0xa, 0x5,
       0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3,
       0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7,
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5,
       0x7, 0x4a, 0xa, 0x7, 0x3, 0x7, 0x2, 0x2, 0x8, 0x2, 0x4, 0x6, 0x8,
       0xa, 0xc, 0x2, 0x4, 0x3, 0x2, 0x7, 0x8, 0x4, 0x2, 0x6, 0x6, 0x9,
       0x9, 0x2, 0x51, 0x2, 0xf, 0x3, 0x2, 0x2, 0x2, 0x4, 0x13, 0x3, 0x2,
       0x2, 0x2, 0x6, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x8, 0x34, 0x3, 0x2, 0x2,
       0x2, 0xa, 0x36, 0x3, 0x2, 0x2, 0x2, 0xc, 0x49, 0x3, 0x2, 0x2, 0x2,
       0xe, 0x10, 0x5, 0x4, 0x3, 0x2, 0xf, 0xe, 0x3, 0x2, 0x2, 0x2, 0x10,
       0x11, 0x3, 0x2, 0x2, 0x2, 0x11, 0xf, 0x3, 0x2, 0x2, 0x2, 0x11, 0x12,
       0x3, 0x2, 0x2, 0x2, 0x12, 0x3, 0x3, 0x2, 0x2, 0x2, 0x13, 0x14, 0x7,
       0x3, 0x2, 0x2, 0x14, 0x17, 0x7, 0x4, 0x2, 0x2, 0x15, 0x18, 0x5, 0xa,
       0x6, 0x2, 0x16, 0x18, 0x5, 0x6, 0x4, 0x2, 0x17, 0x15, 0x3, 0x2, 0x2,
       0x2, 0x17, 0x16, 0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0x3, 0x2, 0x2, 0x2,
       0x19, 0x1a, 0x7, 0x5, 0x2, 0x2, 0x1a, 0x5, 0x3, 0x2, 0x2, 0x2, 0x1b,
       0x1c, 0x7, 0xa, 0x2, 0x2, 0x1c, 0x20, 0x7, 0x3, 0x2, 0x2, 0x1d, 0x1f,
       0x7, 0xa, 0x2, 0x2, 0x1e, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x22, 0x3,
       0x2, 0x2, 0x2, 0x20, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x3, 0x2,
       0x2, 0x2, 0x21, 0x23, 0x3, 0x2, 0x2, 0x2, 0x22, 0x20, 0x3, 0x2, 0x2,
       0x2, 0x23, 0x25, 0x7, 0x5, 0x2, 0x2, 0x24, 0x26, 0x5, 0x8, 0x5, 0x2,
       0x25, 0x24, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x3, 0x2, 0x2, 0x2, 0x27,
       0x25, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x3, 0x2, 0x2, 0x2, 0x28, 0x7,
       0x3, 0x2, 0x2, 0x2, 0x29, 0x35, 0x5, 0x4, 0x3, 0x2, 0x2a, 0x35, 0x5,
       0xc, 0x7, 0x2, 0x2b, 0x2c, 0x7, 0x3, 0x2, 0x2, 0x2c, 0x30, 0x7, 0xa,
       0x2, 0x2, 0x2d, 0x2f, 0x5, 0x8, 0x5, 0x2, 0x2e, 0x2d, 0x3, 0x2, 0x2,
       0x2, 0x2f, 0x32, 0x3, 0x2, 0x2, 0x2, 0x30, 0x2e, 0x3, 0x2, 0x2, 0x2,
       0x30, 0x31, 0x3, 0x2, 0x2, 0x2, 0x31, 0x33, 0x3, 0x2, 0x2, 0x2, 0x32,
       0x30, 0x3, 0x2, 0x2, 0x2, 0x33, 0x35, 0x7, 0x5, 0x2, 0x2, 0x34, 0x29,
       0x3, 0x2, 0x2, 0x2, 0x34, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x34, 0x2b, 0x3,
       0x2, 0x2, 0x2, 0x35, 0x9, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x7, 0xa,
       0x2, 0x2, 0x37, 0x38, 0x5, 0xc, 0x7, 0x2, 0x38, 0xb, 0x3, 0x2, 0x2,
       0x2, 0x39, 0x3a, 0x7, 0x6, 0x2, 0x2, 0x3a, 0x4a, 0x5, 0xc, 0x7, 0x2,
       0x3b, 0x3c, 0x9, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x5, 0xc, 0x7, 0x2, 0x3d,
       0x3e, 0x5, 0xc, 0x7, 0x2, 0x3e, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40,
       0x9, 0x3, 0x2, 0x2, 0x40, 0x41, 0x5, 0xc, 0x7, 0x2, 0x41, 0x42, 0x5,
       0xc, 0x7, 0x2, 0x42, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x7, 0x3,
       0x2, 0x2, 0x44, 0x45, 0x5, 0xc, 0x7, 0x2, 0x45, 0x46, 0x7, 0x5, 0x2,
       0x2, 0x46, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x47, 0x4a, 0x7, 0xb, 0x2, 0x2,
       0x48, 0x4a, 0x7, 0xa, 0x2, 0x2, 0x49, 0x39, 0x3, 0x2, 0x2, 0x2, 0x49,
       0x3b, 0x3, 0x2, 0x2, 0x2, 0x49, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x49, 0x43,
       0x3, 0x2, 0x2, 0x2, 0x49, 0x47, 0x3, 0x2, 0x2, 0x2, 0x49, 0x48, 0x3,
       0x2, 0x2, 0x2, 0x4a, 0xd, 0x3, 0x2, 0x2, 0x2, 0x9, 0x11, 0x17, 0x20,
       0x27, 0x30, 0x34, 0x49,
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

NodeLangParser::Initializer NodeLangParser::_init;
