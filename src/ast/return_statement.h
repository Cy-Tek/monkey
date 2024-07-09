#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class ReturnStatement : public Statement {
public:
  ReturnStatement() = default;
  ReturnStatement(Token token, OwnedExpression value);

  auto debug_print(std::ostream&) const -> void override;

  [[nodiscard]] auto token_literal() const -> std::string override;

  [[nodiscard]] auto Tok() const -> const Token&;
  [[nodiscard]] auto Value() const -> const Expression&;

private:
  Token                       m_token{};
  OwnedExpression m_return_value{nullptr};
};

} // namespace ast
