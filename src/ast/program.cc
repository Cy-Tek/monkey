#include "program.h"

namespace ast {

auto Program::TokenLiteral() const -> std::string {
  if (!m_statements.empty()) {
    return m_statements[0]->TokenLiteral();
  }

  return "";
}

}// namespace ast
