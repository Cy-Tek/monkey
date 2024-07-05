#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class InfixExpression : public Expression {
public:
  InfixExpression() = delete;
  InfixExpression(Token, std::string, std::unique_ptr<Expression>&&,
                  std::unique_ptr<Expression>&&);

  [[nodiscard]] auto token_literal() const -> std::string override;
  auto               debug_print(std::ostream&) const -> void override;

  [[nodiscard]] auto token() const noexcept -> const Token&;
  [[nodiscard]] auto op() const noexcept -> std::string_view;
  [[nodiscard]] auto left() const noexcept -> const Expression&;
  [[nodiscard]] auto right() const noexcept -> const Expression&;

private:
  Token                       m_token;
  std::string                 m_op;
  std::unique_ptr<Expression> m_left;
  std::unique_ptr<Expression> m_right;
};

} // namespace ast
