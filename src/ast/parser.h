#pragma once

#include "lexer.h"
#include "program.h"
#include "token.h"

namespace ast {

class Parser {
 public:
  Parser() = delete;

  explicit Parser(std::string input);

  Parser(Parser &other) = delete;
  auto operator=(Parser &other) -> Parser & = delete;

  Parser(Parser &&other) = delete;
  auto operator=(Parser &&other) -> Parser & = delete;

  auto ParseProgram() -> Program;

 private:
  auto NextToken() -> void;

  lexer::Lexer m_lexer;

  Token m_cur_token = Token{};
  Token m_peek_token = Token{};
};

}// namespace ast
