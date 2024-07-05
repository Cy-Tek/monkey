#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class PrefixExpression : public Expression {
public:
  PrefixExpression() = default;
  PrefixExpression(Token, std::string, std::unique_ptr<Expression>&&);

  [[nodiscard]] auto token() const -> const Token&;
  [[nodiscard]] auto op() const -> const std::string&;
  [[nodiscard]] auto right() const -> const Expression&;

  auto               debug_print(std::ostream&) const -> void override;
  [[nodiscard]] auto token_literal() const -> std::string override;

private:
  Token                       m_token;
  std::string                 m_operator;
  std::unique_ptr<Expression> m_right;
};

} // namespace ast
