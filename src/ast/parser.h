#pragma once

#include "ast.h"
#include "lexer.h"
#include "program.h"
#include "token.h"

namespace ast {

class Statement;
class LetStatement;
class ReturnStatement;
class ExpressionStatement;

enum class Precedence;

using PrefixParseFn = std::function<OwnedExpression()>;
using InfixParseFn  = std::function<OwnedExpression(OwnedExpression&&)>;

class Parser {
public:
  Parser() = delete;

  explicit Parser(std::string);

  Parser(Parser&)                     = delete;
  auto operator=(Parser) -> Parser&   = delete;
  Parser(Parser&&)                    = delete;
  auto operator=(Parser&&) -> Parser& = delete;

  auto parse_program() -> Program;

  [[nodiscard]] auto errors() const noexcept -> const std::vector<std::string>&;

private:
  auto next_token() -> void;

  auto parse_statement() -> OwnedStatement;
  auto parse_let_statement() -> std::unique_ptr<LetStatement>;
  auto parse_return_statement() -> std::unique_ptr<ReturnStatement>;
  auto parse_expression_statement() -> std::unique_ptr<ExpressionStatement>;

  [[nodiscard]] auto parse_expression(Precedence) -> OwnedExpression;

  [[nodiscard]] auto parse_prefix_expression() -> OwnedExpression;

  [[nodiscard]] auto
  parse_infix_expression(OwnedExpression&&) -> OwnedExpression;

  [[nodiscard]] auto parse_grouped_expression() -> OwnedExpression;
  [[nodiscard]] auto parse_identifier() -> OwnedExpression;

  [[nodiscard]] auto parse_integer_literal() const -> OwnedExpression;

  [[nodiscard]] auto parse_boolean_literal() const -> OwnedExpression;

  [[nodiscard]] auto cur_token_is(TokenType) const noexcept -> bool;
  [[nodiscard]] auto peek_token_is(TokenType) const noexcept -> bool;
  [[nodiscard]] auto peek_precedence() const noexcept -> Precedence;
  [[nodiscard]] auto cur_precedence() const noexcept -> Precedence;

  auto expect_peek(TokenType) -> bool;
  auto peek_error(TokenType) -> void;
  auto no_prefix_parse_fn_error(TokenType) -> void;

  auto register_prefix(TokenType, const PrefixParseFn&) -> void;
  auto register_infix(TokenType, const InfixParseFn&) -> void;

  lexer::Lexer m_lexer;

  Token m_cur_token  = Token{};
  Token m_peek_token = Token{};

  std::map<TokenType, PrefixParseFn> m_prefix_parse_fns{};
  std::map<TokenType, InfixParseFn>  m_infix_parse_fns{};

  std::vector<std::string> m_errors{};
};

} // namespace ast
