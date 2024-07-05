#pragma once

#include "ast.h"
#include "identifier.h"
#include "token.h"

namespace ast {

class LetStatement : public Statement {
public:
  LetStatement() = default;
  LetStatement(Token, Identifier, std::unique_ptr<Expression>);

  [[nodiscard]] auto token_literal() const -> std::string override;
  auto               debug_print(std::ostream&) const -> void override;

  [[nodiscard]] auto name() const -> const Identifier&;
  [[nodiscard]] auto token() const -> const Token&;
  [[nodiscard]] auto value() const -> const Expression*;

private:
  Token                       m_token;
  Identifier                  m_name;
  std::unique_ptr<Expression> m_value;
};

} // namespace ast

auto operator<<(std::ostream&, const ast::LetStatement&) -> std::ostream&;
