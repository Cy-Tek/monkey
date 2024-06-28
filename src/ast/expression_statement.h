#pragma once

#include "ast.h"
#include "token.h"
#include <memory>

namespace ast {

class ExpressionStatement : public Statement {
 public:
  ExpressionStatement() = default;
  ExpressionStatement(Token token, std::unique_ptr<Expression> value);

  [[nodiscard]] auto TokenLiteral() const -> std::string override;
  auto DebugPrint(std::ostream&) const -> void override;

  auto Tok() const -> const Token&;
  auto Value() const -> const Expression&;

 private:
  Token m_token{};
  std::unique_ptr<Expression> m_value{nullptr};
};

}// namespace ast
