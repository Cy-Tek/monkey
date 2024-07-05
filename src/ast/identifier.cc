#include "identifier.h"

namespace ast {

Identifier::Identifier(Token token, std::string value)
    : m_token{std::move(token)}, m_value{std::move(value)} {}

auto Identifier::token_literal() const -> std::string {
  auto tok_literal = m_token.literal();
  return tok_literal;
}

auto Identifier::debug_print(std::ostream& os) const -> void {
  os << m_value;
}

auto Identifier::token() const -> const Token& {
  return m_token;
}

auto Identifier::value() const -> const std::string& {
  return m_value;
}

} // namespace ast
