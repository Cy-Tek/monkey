#pragma once

#include "ast.h"
#include <vector>

namespace ast {

class Program : public Node {
 public:
  Program() = default;
  ~Program() = default;

  Program(Program &&other) noexcept = default;
  auto operator=(Program &&other) noexcept -> Program & = default;

  [[nodiscard]] auto TokenLiteral() const -> std::string override;

  auto Statements() -> std::vector<std::unique_ptr<Statement>> &;
  auto AddStatement(std::unique_ptr<Statement> &&statement) -> void;

 private:
  std::vector<std::unique_ptr<Statement>> m_statements{};
};

}// namespace ast
