#include "let_statement.h"

namespace ast {

LetStatement::LetStatement(Token token, Identifier name,
                           OwnedExpression value)
    : m_token{std::move(token)}, m_name{std::move(name)},
      m_value{std::move(value)} {}

auto LetStatement::token_literal() const -> std::string {
  return this->m_token.literal();
}

auto LetStatement::debug_print(std::ostream& os) const -> void {
  os << token_literal() << " " << name() << " = ";

  if (m_value) { os << *m_value; }

  os << ";";
}

auto LetStatement::name() const -> const Identifier& {
  return m_name;
}

auto LetStatement::token() const -> const Token& {
  return m_token;
}

auto LetStatement::value() const -> const Expression* {
  return m_value.get();
}

} // namespace ast
