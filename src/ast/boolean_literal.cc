#include "boolean_literal.h"

namespace ast {

BooleanLiteral::BooleanLiteral(Token token, bool value)
    : m_token(std::move(token)), m_value(value) {}

auto BooleanLiteral::debug_print(std::ostream& os) const -> void {
  os << m_token.literal();
}

auto BooleanLiteral::token_literal() const -> std::string {
  return m_token.literal();
}

auto BooleanLiteral::token() const noexcept -> const Token& {
  return m_token;
}

auto BooleanLiteral::value() const noexcept -> bool {
  return m_value;
}

} // namespace ast
