#include "parser.h"
#include "return_statement.h"
#include "token.h"
#include <memory>

namespace ast {

Parser::Parser(std::string input) : m_lexer{std::move(input)} {
  NextToken();
  NextToken();
}

auto Parser::ParseProgram() -> Program {
  auto program = Program{};

  while (m_cur_token.Type() != TokenType::EoF) {
    auto&& stmt = ParseStatement();
    if (stmt != nullptr) {
      program.AddStatement(std::move(stmt));
    }

    NextToken();
  }

  return program;
}

auto Parser::Errors() const noexcept -> const std::vector<std::string>& {
  return m_errors;
}

auto Parser::NextToken() -> void {
  m_cur_token = std::move(m_peek_token);
  m_peek_token = m_lexer.NextToken();
}

auto Parser::ParseStatement() -> std::unique_ptr<Statement> {
  switch (m_cur_token.Type()) {
    case TokenType::Let: return ParseLetStatement();
    case TokenType::Return: return ParseReturnStatement();
    default: return nullptr;
  }
}

auto Parser::ParseLetStatement() -> std::unique_ptr<LetStatement> {
  auto token = m_cur_token;

  if (!ExpectPeek(TokenType::Ident)) {
    return nullptr;
  }

  auto&& name = Identifier{m_cur_token, m_cur_token.Literal()};

  if (!ExpectPeek(TokenType::Assign)) {
    return nullptr;
  }

  // TODO: We're skipping parsing expressions for now
  while (m_cur_token.Type() != TokenType::Semicolon) {
    NextToken();
  }

  return std::make_unique<LetStatement>(token, std::move(name), nullptr);
}

auto Parser::ParseReturnStatement() -> std::unique_ptr<ReturnStatement> {
  auto token = std::move(m_cur_token);

  NextToken();

  // TODO: We're skipping parsing expressions for now
  while (m_cur_token.Type() != TokenType::Semicolon) {
    NextToken();
  }

  return std::make_unique<ReturnStatement>(token, nullptr);
}

auto Parser::CurTokenIs(TokenType t_type) const -> bool {
  return m_cur_token.Type() == t_type;
}

auto Parser::PeekTokenIs(TokenType t_type) const -> bool {
  return m_peek_token.Type() == t_type;
}

auto Parser::ExpectPeek(const TokenType t_type) -> bool {
  if (PeekTokenIs(t_type)) {
    NextToken();
    return true;
  }

  PeekError(t_type);
  return false;
}

auto Parser::PeekError(TokenType t_type) -> void {
  auto msg = std::format(
      "Expected next token to be {}, got {} instead",
      tokenTypeToString(t_type),
      tokenTypeToString(m_peek_token.Type()));

  m_errors.push_back(std::move(msg));
}

}// namespace ast
