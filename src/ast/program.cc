#include "program.h"

namespace ast {

auto Program::TokenLiteral() const -> std::string {
  if (!m_statements.empty()) {
    return m_statements[0]->TokenLiteral();
  }

  return "";
}

auto Program::Statements() -> std::vector<std::unique_ptr<Statement>> & {
  return m_statements;
}

}// namespace ast
