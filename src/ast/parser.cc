#include "parser.h"

#include "expression_statement.h"
#include "identifier.h"
#include "let_statement.h"
#include "return_statement.h"

namespace ast {

enum class Precedence {
  Lowest,
  Equals,     // ==
  LessGreater,// < or >
  Sum,        // +
  Product,    // *
  Prefix,     // -X or !X
  Call,       // myFunction(X)
};

Parser::Parser(std::string input) : m_lexer{std::move(input)} {
  next_token();
  next_token();

  register_prefix(TokenType::Ident, [this] { return this->parse_identifier(); });
}

auto Parser::parse_program() -> Program {
  auto program = Program{};

  while (m_cur_token.type() != TokenType::EoF) {
    if (auto&& stmt = parse_statement(); stmt != nullptr) {
      program.add_statement(std::move(stmt));
    }

    next_token();
  }

  return program;
}

auto Parser::errors() const noexcept -> const std::vector<std::string>& {
  return m_errors;
}

auto Parser::next_token() -> void {
  m_cur_token = std::move(m_peek_token);
  m_peek_token = m_lexer.next_token();
}

auto Parser::parse_statement() -> std::unique_ptr<Statement> {
  switch (m_cur_token.type()) {
    case TokenType::Let: return parse_let_statement();
    case TokenType::Return: return parse_return_statement();
    default: return parse_expression_statement();
  }
}

auto Parser::parse_let_statement() -> std::unique_ptr<LetStatement> {
  auto token = m_cur_token;

  if (!expect_peek(TokenType::Ident)) {
    return nullptr;
  }

  auto&& name = Identifier{m_cur_token, m_cur_token.literal()};

  if (!expect_peek(TokenType::Assign)) {
    return nullptr;
  }

  // TODO: We're skipping parsing expressions for now
  while (m_cur_token.type() != TokenType::Semicolon) {
    next_token();
  }

  return std::make_unique<LetStatement>(token, std::move(name), nullptr);
}

auto Parser::parse_return_statement() -> std::unique_ptr<ReturnStatement> {
  auto token = m_cur_token;

  next_token();

  // TODO: We're skipping parsing expressions for now
  while (m_cur_token.type() != TokenType::Semicolon) {
    next_token();
  }

  return std::make_unique<ReturnStatement>(token, nullptr);
}

auto Parser::parse_expression_statement() -> std::unique_ptr<ExpressionStatement> {
  auto token = m_cur_token;
  auto expression = parse_expression(Precedence::Lowest);

  if (peek_token_is(TokenType::Semicolon)) {
    next_token();
  }

  return std::make_unique<ExpressionStatement>(token, std::move(expression));
}

auto Parser::parse_expression(Precedence precedence) -> std::unique_ptr<Expression> {
  auto prefix = m_prefix_parse_fns.find(m_cur_token.type());
  if (prefix == m_prefix_parse_fns.end()) return nullptr;

  auto left_expr = prefix->second();
  return left_expr;
}

auto Parser::parse_identifier() -> std::unique_ptr<Expression> {
  return std::make_unique<Identifier>(m_cur_token, m_cur_token.literal());
}

auto Parser::cur_token_is(TokenType t_type) const -> bool {
  return m_cur_token.type() == t_type;
}

auto Parser::peek_token_is(TokenType t_type) const -> bool {
  return m_peek_token.type() == t_type;
}

auto Parser::expect_peek(const TokenType t_type) -> bool {
  if (peek_token_is(t_type)) {
    next_token();
    return true;
  }

  peek_error(t_type);
  return false;
}

auto Parser::peek_error(const TokenType t_type) -> void {
  auto msg = std::format(
      "Expected next token to be {}, got {} instead",
      tokenTypeToString(t_type),
      tokenTypeToString(m_peek_token.type()));

  m_errors.push_back(std::move(msg));
}

auto Parser::register_prefix(const TokenType token_type, const PrefixParseFn& parse_fn) -> void {
  m_prefix_parse_fns[token_type] = parse_fn;
}

auto Parser::register_infix(const TokenType token_type, const InfixParseFn& parse_fn) -> void {
  m_infix_parse_fns[token_type] = parse_fn;
}

}// namespace ast
