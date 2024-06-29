#include "parser.h"

namespace ast {

Parser::Parser(std::string input) : m_lexer{std::move(input)} {
  NextToken();
  NextToken();
}

auto Parser::parse_program() -> Program {
  auto program = Program{};

  while (m_cur_token.type() != TokenType::EoF) {
    auto&& stmt = parse_statement();
    if (stmt != nullptr) {
      program.add_statement(std::move(stmt));
    }

    NextToken();
  }

  return program;
}

auto Parser::errors() const noexcept -> const std::vector<std::string>& {
  return m_errors;
}

auto Parser::NextToken() -> void {
  m_cur_token = std::move(m_peek_token);
  m_peek_token = m_lexer.next_token();
}

auto Parser::parse_statement() -> std::unique_ptr<Statement> {
  switch (m_cur_token.type()) {
    case TokenType::Let: return parse_let_statement();
    case TokenType::Return: return parse_return_statement();
    default: return nullptr;
  }
}

auto Parser::parse_let_statement() -> std::unique_ptr<LetStatement> {
  auto token = m_cur_token;

  if (!expect_peek(TokenType::Ident)) {
    return nullptr;
  }

  auto&& name = Identifier{m_cur_token, m_cur_token.literal()};

  if (!expect_peek(TokenType::Assign)) {
    return nullptr;
  }

  // TODO: We're skipping parsing expressions for now
  while (m_cur_token.type() != TokenType::Semicolon) {
    NextToken();
  }

  return std::make_unique<LetStatement>(token, std::move(name), nullptr);
}

auto Parser::parse_return_statement() -> std::unique_ptr<ReturnStatement> {
  auto token = std::move(m_cur_token);

  NextToken();

  // TODO: We're skipping parsing expressions for now
  while (m_cur_token.type() != TokenType::Semicolon) {
    NextToken();
  }

  return std::make_unique<ReturnStatement>(token, nullptr);
}

auto Parser::cur_token_is(TokenType t_type) const -> bool {
  return m_cur_token.type() == t_type;
}

auto Parser::peek_token_is(TokenType t_type) const -> bool {
  return m_peek_token.type() == t_type;
}

auto Parser::expect_peek(const TokenType t_type) -> bool {
  if (peek_token_is(t_type)) {
    NextToken();
    return true;
  }

  peek_error(t_type);
  return false;
}

auto Parser::peek_error(TokenType t_type) -> void {
  auto msg = std::format(
      "Expected next token to be {}, got {} instead",
      tokenTypeToString(t_type),
      tokenTypeToString(m_peek_token.type()));

  m_errors.push_back(std::move(msg));
}

}// namespace ast
