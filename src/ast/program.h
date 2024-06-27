#pragma once

#include "ast.h"
#include <vector>

namespace ast {

class Program : public Node {
 public:
  [[nodiscard]] auto TokenLiteral() const -> std::string override;

  auto Statements() -> std::vector<std::unique_ptr<Statement>> &;

 private:
  std::vector<std::unique_ptr<Statement>> m_statements{};
};

}// namespace ast
