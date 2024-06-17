#include "lexer.h"
#include "lexer_utils.h"
#include "token.h"

namespace lexer {

Lexer::Lexer(std::string input) : m_input{std::move(input)} { ReadChar(); }

auto Lexer::NextToken() -> Token {
  std::optional<Token> token{};

  SkipWhitespace();

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
      if (isAsciiLetter(m_ch)) {
        auto literal = ReadIdentifier();
        auto type = lookupIdent(literal);

        return Token(type, literal);
      }

      if (isAsciiDigit(m_ch)) {
        return Token(TokenType::Int, ReadNumber());
      }

      token = Token(TokenType::Illegal, {});
  };

  ReadChar();
  return *token;
}

auto Lexer::ReadChar() -> void {
  if (m_read_position >= m_input.size()) {
    m_ch = 0;
  } else {
    m_ch = m_input[m_read_position];
  }

  m_position = m_read_position;
  m_read_position++;
}

auto Lexer::ReadNumber() -> std::string {
  auto position = m_position;
  auto num_chars = 0;

  while (isAsciiDigit(m_ch)) {
    ReadChar();
    num_chars++;
  }

  return m_input.substr(position, num_chars);
}

auto Lexer::ReadIdentifier() -> std::string {
  auto posiiton = m_position;
  auto num_chars = 0;

  while (isAsciiLetter(m_ch)) {
    ReadChar();
    num_chars++;
  }

  return m_input.substr(posiiton, num_chars);
}

auto Lexer::SkipWhitespace() -> void {
  while (isAsciiWhitespace(m_ch)) {
    ReadChar();
  }
}

}// namespace lexer
