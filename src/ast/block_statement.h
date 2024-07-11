#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class BlockStatement : public Statement {
public:
  BlockStatement() = default;
  BlockStatement(Token);

  [[nodiscard]] auto token_literal() const -> std::string override;

  auto debug_print(std::ostream&) const -> void override;

  [[nodiscard]] auto token() const noexcept -> const Token&;

  [[nodiscard]] auto
  statements() const noexcept -> const std::vector<OwnedStatement>&;

private:
  Token                       m_token;
  std::vector<OwnedStatement> m_statements;
};

} // namespace ast
