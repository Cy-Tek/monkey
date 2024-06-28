#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class ReturnStatement : public Statement {
 public:
  ReturnStatement() = default;
  ReturnStatement(Token token, std::unique_ptr<Expression> value);

  auto TokenLiteral() const -> std::string override;

  auto Tok() const -> const Token&;
  auto Value() const -> const Expression&;

 private:
  Token m_token{};
  std::unique_ptr<Expression> m_return_value{nullptr};
};

}// namespace ast
