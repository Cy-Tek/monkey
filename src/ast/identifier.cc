#include "identifier.h"

namespace ast {

Identifier::Identifier(Token token, std::string value)
    : m_token{std::move(token)},
      m_value{std::move(value)} {}

auto Identifier::TokenLiteral() const -> std::string {
  auto tok_literal = m_token.Literal();
  return tok_literal;
}

auto Identifier::Tok() const -> const Token & {
  return m_token;
}

auto Identifier::Value() const -> const std::string & {
  return m_value;
}

}// namespace ast
