#include "let_statement.h"

namespace ast {

LetStatment::LetStatment(Token token, Identifier name, std::unique_ptr<Expression> value)
    : m_token{std::move(token)},
      m_name{std::move(name)},
      m_value{std::move(value)} {}

LetStatment::LetStatment(LetStatment &&other) {
  if (this != &other) {
    m_token = std::move(other.m_token);
    m_name = std::move(other.m_name);
    m_value = std::move(other.m_value);
  }
}

auto LetStatment::operator=(LetStatment &&other) noexcept -> LetStatment & {
  if (this != &other) {
    m_token = std::move(other.m_token);
    m_name = std::move(other.m_name);
    m_value = std::move(other.m_value);
  }

  return *this;
}

}// namespace ast
