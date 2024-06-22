#pragma once

#include "ast.h"
#include "identifier.h"
#include "token.h"

namespace ast {

class LetStatment : public Statement {
  LetStatment(Token token, Identifier name, std::unique_ptr<Expression> value);
  LetStatment(LetStatment &&other);

  auto TokenLiteral() const -> std::string override;

 private:
  Token m_token;
  Identifier m_name;
  std::unique_ptr<Expression> m_value;
};

}// namespace ast
