#pragma once

#include "ast.h"
#include "let_statement.h"
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

  auto ParseStatement() -> std::unique_ptr<Statement>;
  auto ParseLetStatement() -> std::unique_ptr<LetStatement>;

  auto CurTokenIs(TokenType t_type) const -> bool;
  auto PeekTokenIs(TokenType t_type) const -> bool;
  auto ExpectPeek(TokenType t_type) -> bool;

  lexer::Lexer m_lexer;

  Token m_cur_token = Token{};
  Token m_peek_token = Token{};
};

}// namespace ast
