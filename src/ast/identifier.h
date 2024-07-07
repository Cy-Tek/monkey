#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class Identifier : public Expression {
public:
  Identifier() = default;
  Identifier(Token token, std::string value);

       Identifier(Identifier&& other) noexcept               = default;
  auto operator=(Identifier&& other) noexcept -> Identifier& = default;

  [[nodiscard]] auto token_literal() const -> std::string override;
  auto               debug_print(std::ostream&) const -> void override;

  [[nodiscard]] auto token() const -> const Token&;
  [[nodiscard]] auto value() const -> const std::string&;

private:
  Token       m_token;
  std::string m_value;
};

} // namespace ast
