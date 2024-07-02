#include "integer_literal.h"

#include <utility>

namespace ast {

IntegerLiteral::IntegerLiteral(Token token, const int64_t value)
    : m_token{std::move(token)}, m_value{value} {}

auto IntegerLiteral::debug_print(std::ostream& os) const -> void {
  os << m_token.literal();
}

auto IntegerLiteral::token_literal() const -> std::string {
  return m_token.literal();
}

auto IntegerLiteral::token() const -> const Token& {
  return m_token;
}

auto IntegerLiteral::value() const -> int64_t {
  return m_value;
}

}// namespace ast