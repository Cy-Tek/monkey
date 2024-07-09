#include "infix_expression.h"

#include <utility>

namespace ast {

InfixExpression::InfixExpression(Token token, std::string op,
                                 OwnedExpression&& left,
                                 OwnedExpression&& right)
    : m_token{std::move(token)}, m_op{std::move(op)}, m_left{std::move(left)},
      m_right{std::move(right)} {}

auto InfixExpression::token_literal() const -> std::string {
  return m_token.literal();
}

auto InfixExpression::debug_print(std::ostream& os) const -> void {
  os << "(";
  m_left->debug_print(os);
  os << " " << m_op << " ";
  m_right->debug_print(os);
  os << ")";
}

auto InfixExpression::token() const noexcept -> const Token& {
  return m_token;
}

auto InfixExpression::op() const noexcept -> std::string_view {
  return m_op;
}

auto InfixExpression::left() const noexcept -> const Expression& {
  return *m_left;
}

auto InfixExpression::right() const noexcept -> const Expression& {
  return *m_right;
}

} // namespace ast
