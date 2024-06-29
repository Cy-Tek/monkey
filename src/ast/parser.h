#pragma once

#include "ast.h"
#include "let_statement.h"
#include "lexer.h"
#include "program.h"
#include "return_statement.h"
#include "token.h"

namespace ast {

class Parser {
 public:
  Parser() = delete;

  explicit Parser(std::string);

  Parser(Parser&) = delete;
  auto operator=(Parser) -> Parser& = delete;

  Parser(Parser&&) = delete;
  auto operator=(Parser&&) -> Parser& = delete;

  auto parse_program() -> Program;
  [[nodiscard]] auto errors() const noexcept -> const std::vector<std::string>&;

 private:
  auto NextToken() -> void;

  auto parse_statement() -> std::unique_ptr<Statement>;
  auto parse_let_statement() -> std::unique_ptr<LetStatement>;
  auto parse_return_statement() -> std::unique_ptr<ReturnStatement>;

  [[nodiscard]] auto cur_token_is(TokenType) const -> bool;
  [[nodiscard]] auto peek_token_is(TokenType) const -> bool;

  auto expect_peek(TokenType) -> bool;
  auto peek_error(TokenType) -> void;

  lexer::Lexer m_lexer;

  Token m_cur_token = Token{};
  Token m_peek_token = Token{};

  std::vector<std::string> m_errors{};
};

}// namespace ast
