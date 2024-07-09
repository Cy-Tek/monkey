#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class InfixExpression : public Expression {
public:
  InfixExpression() = delete;
  InfixExpression(Token, std::string, OwnedExpression&&, OwnedExpression&&);

  auto debug_print(std::ostream&) const -> void override;

  [[nodiscard]] auto token_literal() const -> std::string override;

  [[nodiscard]] auto token() const noexcept -> const Token&;
  [[nodiscard]] auto op() const noexcept -> std::string_view;
  [[nodiscard]] auto left() const noexcept -> const Expression&;
  [[nodiscard]] auto right() const noexcept -> const Expression&;

private:
  Token           m_token;
  std::string     m_op;
  OwnedExpression m_left;
  OwnedExpression m_right;
};

} // namespace ast
