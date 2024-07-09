#pragma once

#include "ast.h"

namespace ast {

class Program : public Node {
public:
  Program()                         = default;
  Program(Program&& other) noexcept = default;

  auto operator=(Program&& other) noexcept -> Program& = default;

  auto debug_print(std::ostream&) const -> void override;

  [[nodiscard]] auto token_literal() const -> std::string override;

  auto statements() -> std::vector<OwnedStatement>&;
  auto add_statement(OwnedStatement statement) -> void;

private:
  std::vector<OwnedStatement> m_statements{};
};

} // namespace ast
