#pragma once

#include "ast.h"
#include "identifier.h"
#include "token.h"

namespace ast {

class LetStatement : public Statement {
 public:
  LetStatement() = default;
  LetStatement(Token, Identifier, std::unique_ptr<Expression>);

  [[nodiscard]] auto TokenLiteral() const -> std::string override;
  auto DebugPrint(std::ostream&) const -> void override;

  [[nodiscard]] auto Name() const -> const Identifier&;
  [[nodiscard]] auto Tok() const -> const Token&;
  [[nodiscard]] auto Value() const -> const Expression*;

 private:
  Token m_token;
  Identifier m_name;
  std::unique_ptr<Expression> m_value;
};

}// namespace ast

auto operator<<(std::ostream&, const ast::LetStatement&) -> std::ostream&;
