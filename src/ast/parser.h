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

  explicit Parser(std::string input);

  Parser(Parser& other) = delete;
  auto operator=(Parser& other) -> Parser& = delete;

  Parser(Parser&& other) = delete;
  auto operator=(Parser&& other) -> Parser& = delete;

  auto parse_program() -> Program;
  [[nodiscard]] auto errors() const noexcept -> const std::vector<std::string>&;

 private:
  auto NextToken() -> void;

  auto parse_statement() -> std::unique_ptr<Statement>;
  auto parse_let_statement() -> std::unique_ptr<LetStatement>;
  auto parse_return_statement() -> std::unique_ptr<ReturnStatement>;

  [[nodiscard]] auto cur_token_is(TokenType t_type) const -> bool;
  [[nodiscard]] auto peek_token_is(TokenType t_type) const -> bool;

  auto expect_peek(TokenType t_type) -> bool;
  auto peek_error(TokenType t_type) -> void;

  lexer::Lexer m_lexer;

  Token m_cur_token = Token{};
  Token m_peek_token = Token{};

  std::vector<std::string> m_errors{};
};

}// namespace ast
