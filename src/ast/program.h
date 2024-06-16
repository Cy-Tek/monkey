#pragma once

#include "ast.h"

namespace ast {

class Program : public Node {
 public:
  auto tokenLiteral() const -> std::string override;

 private:
  std::vector<std::unique_ptr<Statement>> m_statements;
};

} // namespace ast
