#pragma once

#include "ast.h"

namespace ast {

class LetStatment : public Statement {
 private:
  std::unique_ptr<Expression> value;
};

} // namespace ast
