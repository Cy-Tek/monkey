#include "program.h"

namespace ast {

auto Program::tokenLiteral() const -> std::string {
  if (!m_statements.empty()) {
    return m_statements[0]->tokenLiteral();
  }

  return "";
}

} // namespace ast
