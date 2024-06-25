#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class Identifier : public Expression {
 public:
  Identifier() = default;
  Identifier(Token token, std::string value);

  Identifier(Identifier &&other);
  auto operator=(Identifier &&other) -> Identifier &;

  auto TokenLiteral() const -> std::string override;

 private:
  Token m_token;
  std::string m_value;
};

}// namespace ast
