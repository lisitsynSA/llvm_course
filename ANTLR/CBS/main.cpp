#include "CBSLexer.h"
#include "CBSListener.h"
#include "CBSParser.h"
#include "antlr4-runtime.h"

class CBSBaseListener : public CBSListener {
public:
  virtual void enterSeq(CBSParser::SeqContext * /*ctx*/) override {
    std::cout << "enterSeq\n";
  }
  virtual void exitSeq(CBSParser::SeqContext * /*ctx*/) override {
    std::cout << "exitSeq\n";
  }

  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override {
    std::cout << "enterEveryRule\n";
  }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override {
    std::cout << "exitEveryRule\n";
  }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override {
    std::cout << "visitTerminal\n";
  }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override {
    std::cout << "visitErrorNode\n";
  }
};

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    std::cout << "[ERROR] Need 1 argument: file with expression\n";
    return 1;
  }
  // Open file
  std::ifstream stream;
  stream.open(argv[1]);

  // Provide the input text in a stream
  antlr4::ANTLRInputStream input(stream);

  // Create a lexer from the input
  CBSLexer lexer(&input);

  // Create a token stream from the lexer
  antlr4::CommonTokenStream tokens(&lexer);

  // Create a parser from the token stream
  CBSParser parser(&tokens);

  // Display the parse tree
  std::cout << "StringTree:\n  " << parser.seq()->toStringTree() << '\n';
  parser.reset();
  std::cout << "\nPretty StringTree:\n"
            << parser.seq()->toStringTree(true) << '\n';
  parser.reset();

  // Create Listener for dumping
  CBSBaseListener *listener = new CBSBaseListener();
  antlr4::tree::ParseTreeWalker::DEFAULT.walk(listener, parser.seq());
  return 0;
}
