#include "expression_statement.h"

#include "token.h"

namespace ast {

ExpressionStatement::ExpressionStatement(Token token, OwnedExpression&& value)
    : m_token{std::move(token)}, m_value(std::move(value)) {}

auto ExpressionStatement::token_literal() const -> std::string {
  return m_token.literal();
}

auto ExpressionStatement::debug_print(std::ostream& os) const -> void {
  if (m_value) { os << *m_value; }
}

auto ExpressionStatement::token() const -> const Token& {
  return m_token;
}

auto ExpressionStatement::value() const -> Expression& {
  return *m_value;
}

} // namespace ast
