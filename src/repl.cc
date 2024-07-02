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
    auto tok = lexer.next_token();

    for (; tok.type() != TokenType::EoF; tok = lexer.next_token()) {
      os << "{ " << tok.type() << ": " << tok.literal() << " }" << std::endl;
    }

    os << prompt;
  }
}
