#include "let_statement.h"

namespace ast {

LetStatement::LetStatement(Token token, Identifier name, std::unique_ptr<Expression> value)
    : m_token{std::move(token)},
      m_name{std::move(name)},
      m_value{std::move(value)} {}

LetStatement::LetStatement(LetStatement &&other)  noexcept {
  if (this != &other) {
    m_token = std::move(other.m_token);
    m_name = std::move(other.m_name);
    m_value = std::move(other.m_value);
  }
}

auto LetStatement::operator=(LetStatement &&other) noexcept -> LetStatement & {
  if (this != &other) {
    m_token = std::move(other.m_token);
    m_name = std::move(other.m_name);
    m_value = std::move(other.m_value);
  }

  return *this;
}

auto LetStatement::TokenLiteral() const -> std::string {
  return this->m_token.Literal();
}

auto LetStatement::Name() const -> const Identifier & {
  return m_name;
}

auto LetStatement::Tok() const -> const Token & {
  return m_token;
}

auto LetStatement::Value() const -> const Expression & {
  return *m_value;
}

}// namespace ast
