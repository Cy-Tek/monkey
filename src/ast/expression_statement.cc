#include "expression_statement.h"
#include "token.h"

namespace ast {

ExpressionStatement::ExpressionStatement(Token token, std::unique_ptr<Expression> value)
    : m_token{std::move(token)},
      m_value(std::move(value)) {}

auto ExpressionStatement::TokenLiteral() const -> std::string {
  return m_token.Literal();
}

auto ExpressionStatement::DebugPrint(std::ostream& os) const -> void {
  if (m_value) {
    os << *m_value;
  }
}

auto ExpressionStatement::Tok() const -> const Token& {
  return m_token;
}

auto ExpressionStatement::Value() const -> const Expression& {
  return *m_value.get();
}

}// namespace ast
