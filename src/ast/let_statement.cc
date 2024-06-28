#include "let_statement.h"

namespace ast {

LetStatement::LetStatement(Token token, Identifier name, std::unique_ptr<Expression> value)
    : m_token{std::move(token)},
      m_name{std::move(name)},
      m_value{std::move(value)} {}

auto LetStatement::TokenLiteral() const -> std::string {
  return this->m_token.Literal();
}

auto LetStatement::DebugPrint(std::ostream& os) const -> void {
  os << TokenLiteral() << " " << Name() << " = ";

  if (m_value) {
    os << *m_value;
  }

  os << ";";
}

auto LetStatement::Name() const -> const Identifier& {
  return m_name;
}

auto LetStatement::Tok() const -> const Token& {
  return m_token;
}

auto LetStatement::Value() const -> const Expression* {
  return m_value.get();
}

}// namespace ast
