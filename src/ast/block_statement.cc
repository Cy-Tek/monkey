#include "./block_statement.h"
#include "block_statement.h"

namespace ast {

BlockStatement::BlockStatement(Token token)
    : m_token{std::move(token)}, m_statements{} {}

auto BlockStatement::token_literal() const -> std::string {
  return m_token.literal();
}

auto BlockStatement::debug_print(std::ostream&) const -> void {}

auto BlockStatement::token() const noexcept -> const Token& {
  return m_token;
}

auto BlockStatement::statements() const noexcept
    -> const std::vector<OwnedStatement>& {
  return m_statements;
}

} // namespace ast
