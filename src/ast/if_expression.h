#pragma once

#include "ast.h"
#include "token.h"

namespace ast {

class IfExpression : public Expression {
private:
  Token                       m_token;
  OwnedExpression condition;
};

} // namespace ast
