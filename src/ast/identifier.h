#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class Identifier : public Expression {
 public:
  Identifier() = default;
  Identifier(Token token, std::string value);

  Identifier(Identifier &&other) noexcept = default;
  auto operator=(Identifier &&other) noexcept -> Identifier & = default;

  [[nodiscard]] auto TokenLiteral() const -> std::string override;

  [[nodiscard]] auto Tok() const -> const Token &;
  [[nodiscard]] auto Value() const -> const std::string &;

 private:
  Token m_token;
  std::string m_value;
};

}// namespace ast
