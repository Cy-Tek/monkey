#include "program.h"

namespace ast {

auto Program::token_literal() const -> std::string {
  if (!m_statements.empty()) { return m_statements[0]->token_literal(); }

  return "";
}

auto Program::debug_print(std::ostream& os) const -> void {
  for (const auto& statement : m_statements) { os << *statement; }
}

auto Program::statements() -> std::vector<OwnedStatement>& {
  return m_statements;
}

auto Program::add_statement(OwnedStatement statement) -> void {
  m_statements.push_back(std::move(statement));
}

} // namespace ast
