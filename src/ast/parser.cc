#include "parser.h"

#include "boolean_literal.h"
#include "expression_statement.h"
#include "identifier.h"
#include "infix_expression.h"
#include "integer_literal.h"
#include "let_statement.h"
#include "prefix_expression.h"
#include "return_statement.h"
#include "token.h"

namespace ast {

enum class Precedence {
  Lowest,
  Equals,      // ==
  LessGreater, // < or >
  Sum,         // +
  Product,     // *
  Prefix,      // -X or !X
  Call,        // myFunction(X)
};

static const std::map<TokenType, Precedence> precedences{
    {TokenType::EQ, Precedence::Equals},
    {TokenType::NotEq, Precedence::Equals},
    {TokenType::LT, Precedence::LessGreater},
    {TokenType::GT, Precedence::LessGreater},
    {TokenType::Plus, Precedence::Sum},
    {TokenType::Minus, Precedence::Sum},
    {TokenType::Asterisk, Precedence::Product},
    {TokenType::Slash, Precedence::Product},
};

Parser::Parser(std::string input) : m_lexer{std::move(input)} {
  next_token();
  next_token();

  register_prefix(TokenType::Ident,
                  [this] { return this->parse_identifier(); });
  register_prefix(TokenType::Int,
                  [this] { return this->parse_integer_literal(); });
  register_prefix(TokenType::False,
                  [this] { return this->parse_boolean_literal(); });
  register_prefix(TokenType::True,
                  [this] { return this->parse_boolean_literal(); });
  register_prefix(TokenType::Bang,
                  [this] { return this->parse_prefix_expression(); });
  register_prefix(TokenType::Minus,
                  [this] { return this->parse_prefix_expression(); });
  register_prefix(TokenType::LParen,
                  [this] { return this->parse_grouped_expression(); });

  register_infix(TokenType::Plus, [this](auto&& expr) {
    return this->parse_infix_expression(std::move(expr));
  });
  register_infix(TokenType::Minus, [this](auto&& expr) {
    return this->parse_infix_expression(std::move(expr));
  });
  register_infix(TokenType::Slash, [this](auto&& expr) {
    return this->parse_infix_expression(std::move(expr));
  });
  register_infix(TokenType::Asterisk, [this](auto&& expr) {
    return this->parse_infix_expression(std::move(expr));
  });
  register_infix(TokenType::EQ, [this](auto&& expr) {
    return this->parse_infix_expression(std::move(expr));
  });
  register_infix(TokenType::NotEq, [this](auto&& expr) {
    return this->parse_infix_expression(std::move(expr));
  });
  register_infix(TokenType::LT, [this](auto&& expr) {
    return this->parse_infix_expression(std::move(expr));
  });
  register_infix(TokenType::GT, [this](auto&& expr) {
    return this->parse_infix_expression(std::move(expr));
  });
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
  m_cur_token  = std::move(m_peek_token);
  m_peek_token = m_lexer.next_token();
}

auto Parser::parse_statement() -> OwnedStatement {
  switch (m_cur_token.type()) {
  case TokenType::Let: return parse_let_statement();
  case TokenType::Return: return parse_return_statement();
  default: return parse_expression_statement();
  }
}

auto Parser::parse_let_statement() -> std::unique_ptr<LetStatement> {
  auto token = m_cur_token;

  if (!expect_peek(TokenType::Ident)) { return nullptr; }

  auto&& name = Identifier{m_cur_token, m_cur_token.literal()};

  if (!expect_peek(TokenType::Assign)) { return nullptr; }

  // TODO: We're skipping parsing expressions for now
  while (m_cur_token.type() != TokenType::Semicolon) { next_token(); }

  return std::make_unique<LetStatement>(token, std::move(name), nullptr);
}

auto Parser::parse_return_statement() -> std::unique_ptr<ReturnStatement> {
  auto token = m_cur_token;

  next_token();

  // TODO: We're skipping parsing expressions for now
  while (m_cur_token.type() != TokenType::Semicolon) { next_token(); }

  return std::make_unique<ReturnStatement>(token, nullptr);
}

auto Parser::parse_expression_statement()
    -> std::unique_ptr<ExpressionStatement> {
  auto token      = m_cur_token;
  auto expression = parse_expression(Precedence::Lowest);

  if (peek_token_is(TokenType::Semicolon)) { next_token(); }

  return std::make_unique<ExpressionStatement>(token, std::move(expression));
}

auto Parser::parse_expression(Precedence precedence) -> OwnedExpression {
  const auto prefix = m_prefix_parse_fns.find(m_cur_token.type());
  if (prefix == m_prefix_parse_fns.end()) {
    no_prefix_parse_fn_error(m_cur_token.type());
    return nullptr;
  }

  auto left_expr = prefix->second();

  while (!peek_token_is(TokenType::Semicolon) &&
         precedence < peek_precedence()) {
    const auto infix = m_infix_parse_fns.find(m_peek_token.type());
    if (infix == m_infix_parse_fns.end()) { return left_expr; }

    next_token();
    left_expr = infix->second(std::move(left_expr));
  }

  return left_expr;
}

auto Parser::parse_prefix_expression() -> OwnedExpression {
  auto token   = m_cur_token;
  auto literal = token.literal();

  next_token();

  auto right = parse_expression(Precedence::Prefix);

  return std::make_unique<PrefixExpression>(token, std::move(literal),
                                            std::move(right));
}

auto Parser::parse_infix_expression(OwnedExpression&& left) -> OwnedExpression {
  auto   token      = m_cur_token;
  auto&& op         = token.literal();
  auto   precedence = cur_precedence();

  next_token();

  auto&& right = parse_expression(precedence);

  return std::make_unique<InfixExpression>(token, std::move(op),
                                           std::move(left), std::move(right));
}

auto Parser::parse_grouped_expression() -> OwnedExpression {
  next_token();

  auto exp = parse_expression(Precedence::Lowest);
  if (!expect_peek(TokenType::RParen)) { return nullptr; }

  return exp;
}

auto Parser::parse_identifier() -> OwnedExpression {
  return std::make_unique<Identifier>(m_cur_token, m_cur_token.literal());
}

auto Parser::parse_integer_literal() const -> OwnedExpression {
  const auto token = m_cur_token;

  try {
    const auto value = std::stoi(token.literal());
    return std::make_unique<IntegerLiteral>(token, value);
  } catch (std::invalid_argument&) { return nullptr; }
}

auto Parser::parse_boolean_literal() const -> OwnedExpression {
  return std::make_unique<BooleanLiteral>(m_cur_token,
                                          cur_token_is(TokenType::True));
}

auto Parser::cur_token_is(const TokenType t_type) const noexcept -> bool {
  return m_cur_token.type() == t_type;
}

auto Parser::peek_token_is(const TokenType t_type) const noexcept -> bool {
  return m_peek_token.type() == t_type;
}

auto Parser::peek_precedence() const noexcept -> Precedence {
  try {
    return precedences.at(m_peek_token.type());
  } catch (const std::out_of_range&) { return Precedence::Lowest; }
}

auto Parser::cur_precedence() const noexcept -> Precedence {
  try {
    return precedences.at(m_cur_token.type());
  } catch (const std::out_of_range&) { return Precedence::Lowest; }
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
  auto msg = std::format("Expected next token to be {}, got {} instead",
                         to_string(t_type), to_string(m_peek_token.type()));

  m_errors.push_back(std::move(msg));
}

auto Parser::no_prefix_parse_fn_error(const TokenType t_type) -> void {
  auto msg =
      std::format("No prefix parse function for {} found", to_string(t_type));
  m_errors.push_back(std::move(msg));
}

auto Parser::register_prefix(const TokenType      token_type,
                             const PrefixParseFn& parse_fn) -> void {
  m_prefix_parse_fns[token_type] = parse_fn;
}

auto Parser::register_infix(const TokenType     token_type,
                            const InfixParseFn& parse_fn) -> void {
  m_infix_parse_fns[token_type] = parse_fn;
}

} // namespace ast
