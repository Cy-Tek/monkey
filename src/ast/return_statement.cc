#include "return_statement.h"
#include "ast.h"

namespace ast {

ReturnStatement::ReturnStatement(Token token, OwnedExpression value)
    : m_token{std::move(token)}, m_return_value{std::move(value)} {}

auto ReturnStatement::token_literal() const -> std::string {
  return m_token.literal();
}

auto ReturnStatement::debug_print(std::ostream& os) const -> void {
  os << token_literal() << " ";

  if (m_return_value) { os << *m_return_value; }

  os << ";";
}

auto ReturnStatement::Tok() const -> const Token& {
  return m_token;
}

auto ReturnStatement::Value() const -> const Expression& {
  return *m_return_value.get();
}

} // namespace ast
