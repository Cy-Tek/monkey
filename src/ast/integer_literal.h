#pragma once

#include "ast.h"

#include <token.h>

namespace ast {

class IntegerLiteral : public Expression {
public:
  IntegerLiteral() = default;
  IntegerLiteral(Token, int64_t);

  auto               debug_print(std::ostream&) const -> void override;
  [[nodiscard]] auto token_literal() const -> std::string override;

  [[nodiscard]] auto token() const -> const Token&;
  [[nodiscard]] auto value() const -> int64_t;

private:
  Token   m_token;
  int64_t m_value;
};

} // namespace ast
