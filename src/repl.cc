#include "repl.h"

#include "lexer.h"
#include "str_utils.h"
#include "token.h"

auto startRepl(std::istream &is, std::ostream &os) -> void {
  const auto prompt = ">> ";
  std::string line;

  os << prompt;

  while (std::getline(is, line)) {
    utils::trim(line);

    if (line.empty())
      continue;
    else if (line == "quit;")
      break;

    auto lexer = lexer::Lexer(line);
    auto tok = lexer.NextToken();

    for (; tok.Type() != TokenType::EoF; tok = lexer.NextToken()) {
      os << "{ " << tok.Type() << ": " << tok.Literal() << " }" << std::endl;
    }

    os << prompt;
  }
}
