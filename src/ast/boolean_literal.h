#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class BooleanLiteral : public Expression {
public:
  BooleanLiteral() = default;
  BooleanLiteral(Token, bool);

  auto debug_print(std::ostream&) const -> void override;

  [[nodiscard]] auto token_literal() const -> std::string override;

  [[nodiscard]] auto token() const noexcept -> const Token&;
  [[nodiscard]] auto value() const noexcept -> bool;

private:
  Token m_token;
  bool  m_value{false};
};

} // namespace ast
