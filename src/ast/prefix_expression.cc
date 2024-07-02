#include "prefix_expression.h"

namespace ast {

PrefixExpression::PrefixExpression(Token token, std::string op, std::unique_ptr<Expression>&& right)
    : m_token{std::move(token)},
      m_operator{std::move(op)},
      m_right(std::move(right)) {}

auto PrefixExpression::token() const -> const Token& {
  return m_token;
}

auto PrefixExpression::op() const -> const std::string& {
  return m_operator;
}

auto PrefixExpression::right() const -> const Expression& {
  return *m_right;
}

auto PrefixExpression::debug_print(std::ostream& os) const -> void {
  os << "(" << m_operator;
  m_right->debug_print(os);
  os << ")";
}

auto PrefixExpression::token_literal() const -> std::string {
  return m_token.literal();
}

}// namespace ast
