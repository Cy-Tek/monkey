#include "parser.h"
#include "program.h"
#include "token.h"

namespace ast {

Parser::Parser(std::string input) : m_lexer{input} {
  NextToken();
  NextToken();
}

auto Parser::ParseProgram() -> Program {
  auto program = Program{};

  while (m_cur_token.Type() != TokenType::EoF) {
    auto &&stmt = ParseStatement();
    if (stmt != nullptr) {
      program.AddStatement(std::move(stmt));
    }

    NextToken();
  }

  return program;
}

auto Parser::NextToken() -> void {
  m_cur_token = std::move(m_peek_token);
  m_peek_token = m_lexer.NextToken();
}

auto Parser::ParseStatement() -> std::unique_ptr<Statement> {
  switch (m_cur_token.Type()) {
    case TokenType::Let: return ParseLetStatement();
    default: return nullptr;
  }
}

auto Parser::ParseLetStatement() -> std::unique_ptr<LetStatement> {
  auto token = m_cur_token;

  if (!ExpectPeek(TokenType::Ident)) {
    return nullptr;
  }

  auto &&name = Identifier{m_cur_token, m_cur_token.Literal()};

  if (!ExpectPeek(TokenType::Assign)) {
    return nullptr;
  }

  return std::make_unique<LetStatement>(token, std::move(name), nullptr);
}

auto Parser::CurTokenIs(TokenType t_type) const -> bool {
  return m_cur_token.Type() == t_type;
}

auto Parser::PeekTokenIs(TokenType t_type) const -> bool {
  return m_peek_token.Type() == t_type;
}

auto Parser::ExpectPeek(TokenType t_type) -> bool {
  if (PeekTokenIs(t_type)) {
    NextToken();
    return true;
  }

  return false;
}

}// namespace ast
