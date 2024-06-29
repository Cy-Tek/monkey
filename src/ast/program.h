#pragma once

#include "ast.h"

namespace ast {

class Program : public Node {
 public:
  Program() = default;

  Program(Program&& other) noexcept = default;
  auto operator=(Program&& other) noexcept -> Program& = default;

  [[nodiscard]] auto token_literal() const -> std::string override;
  auto debug_print(std::ostream&) const -> void override;

  auto statements() -> std::vector<std::unique_ptr<Statement>>&;
  auto add_statement(std::unique_ptr<Statement> statement) -> void;

 private:
  std::vector<std::unique_ptr<Statement>> m_statements{};
};

}// namespace ast
