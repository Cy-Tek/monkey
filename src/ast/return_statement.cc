#include "return_statement.h"
#include "ast.h"

namespace ast {

ReturnStatement::ReturnStatement(Token token, std::unique_ptr<Expression> value) : m_token{std::move(token)},
                                                                                   m_return_value{std::move(value)} {}

auto ReturnStatement::TokenLiteral() const -> std::string {
  return m_token.Literal();
}

auto ReturnStatement::Tok() const -> const Token& {
  return m_token;
}

auto ReturnStatement::Value() const -> const Expression& {
  return *m_return_value.get();
}

}// namespace ast
