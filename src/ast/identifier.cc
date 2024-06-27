#include "identifier.h"

namespace ast {

Identifier::Identifier(Token token, std::string value)
    : m_token{std::move(token)},
      m_value{std::move(value)} {}

Identifier::Identifier(Identifier &&other) noexcept {
  if (this != &other) {
    m_token = std::move(other.m_token);
    m_value = std::move(other.m_value);
  }
}

auto Identifier::operator=(Identifier &&other) noexcept -> Identifier & {
  if (this != &other) {
    m_token = std::move(other.m_token);
    m_value = std::move(other.m_value);
  }

  return *this;
}

auto Identifier::TokenLiteral() const -> std::string {
  return m_token.Literal();
}

auto Identifier::Tok() const -> const Token & {
  return m_token;
}

auto Identifier::Value() const -> const std::string & {
  return m_value;
}

}// namespace ast
