#include "parser.h"

namespace ast {

Parser::Parser(std::string input) : m_lexer{input} {
  NextToken();
  NextToken();
}

auto Parser::ParseProgram() -> Program {
}

auto Parser::NextToken() -> void {
  m_cur_token = std::move(m_peek_token);
  m_peek_token = m_lexer.NextToken();
}

}// namespace ast
