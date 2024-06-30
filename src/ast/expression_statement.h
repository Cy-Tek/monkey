#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class ExpressionStatement : public Statement {
 public:
  ExpressionStatement() = default;
  ExpressionStatement(Token token, std::unique_ptr<Expression> value);

  [[nodiscard]] auto token_literal() const -> std::string override;
  auto debug_print(std::ostream&) const -> void override;

  [[nodiscard]] auto token() const -> const Token&;
  [[nodiscard]] auto value() const -> Expression&;

 private:
  Token m_token{};
  std::unique_ptr<Expression> m_value{nullptr};
};

}// namespace ast
