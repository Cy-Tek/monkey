#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class PrefixExpression : public Expression {
public:
  PrefixExpression() = default;
  PrefixExpression(Token, std::string, OwnedExpression&&);

  auto debug_print(std::ostream&) const -> void override;

  [[nodiscard]] auto token_literal() const -> std::string override;

  [[nodiscard]] auto token() const -> const Token&;
  [[nodiscard]] auto op() const -> const std::string&;
  [[nodiscard]] auto right() const -> const Expression&;

private:
  Token           m_token;
  std::string     m_operator;
  OwnedExpression m_right;
};

} // namespace ast
