#include "lexer.h"
#include "token.h"

namespace lexer {

Lexer::Lexer(std::string input) : m_input{std::move(input)} { ReadChar(); }

auto Lexer::ReadChar() -> void {
  if (m_read_position >= m_input.size()) {
    m_ch = 0;
  } else {
    m_ch = m_input[m_read_position];
  }

  m_position = m_read_position;
  m_read_position++;
}

auto Lexer::NextToken() -> Token {
  std::optional<Token> token{};

  switch (m_ch) {
    case '=':
      token = Token(TokenType::Assign, std::string{m_ch});
      break;
    case ';':
      token = Token(TokenType::Semicolon, std::string{m_ch});
      break;
    case ',':
      token = Token(TokenType::Comma, std::string{m_ch});
      break;
    case '(':
      token = Token(TokenType::LParen, std::string{m_ch});
      break;
    case ')':
      token = Token(TokenType::RParen, std::string{m_ch});
      break;
    case '{':
      token = Token(TokenType::LBrace, std::string{m_ch});
      break;
    case '}':
      token = Token(TokenType::RBrace, std::string{m_ch});
      break;
    case '+':
      token = Token(TokenType::Plus, std::string{m_ch});
      break;
    case '\0':
      token = Token(TokenType::EoF, {});
      break;
    default:
      token = Token(TokenType::Illegal, {});
  };

  ReadChar();
  return *token;
}

}// namespace lexer
