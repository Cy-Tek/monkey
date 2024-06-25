#include "lexer.h"
#include "token.h"

#include "str_utils.h"

namespace lexer {

Lexer::Lexer(std::string input) : m_input{std::move(input)} { ReadChar(); }

auto Lexer::NextToken() -> Token {
  std::optional<Token> token{};

  SkipWhitespace();

  switch (m_ch) {
    case '=':
      if (PeekChar() == '=') {
        ReadChar();
        token = Token{TokenType::EQ, "=="};
      } else {
        token = Token{TokenType::Assign, std::string{m_ch}};
      }

      break;
    case ';':
      token = Token{TokenType::Semicolon, std::string{m_ch}};
      break;
    case ',':
      token = Token{TokenType::Comma, std::string{m_ch}};
      break;
    case '(':
      token = Token{TokenType::LParen, std::string{m_ch}};
      break;
    case ')':
      token = Token{TokenType::RParen, std::string{m_ch}};
      break;
    case '{':
      token = Token{TokenType::LBrace, std::string{m_ch}};
      break;
    case '}':
      token = Token{TokenType::RBrace, std::string{m_ch}};
      break;
    case '+':
      token = Token{TokenType::Plus, std::string{m_ch}};
      break;
    case '-':
      token = Token{TokenType::Minus, std::string{m_ch}};
      break;
    case '!':
      if (PeekChar() == '=') {
        ReadChar();
        token = Token{TokenType::NotEq, "!="};
      } else {
        token = Token{TokenType::Bang, std::string{m_ch}};
      }

      break;
    case '/':
      token = Token{TokenType::Slash, std::string{m_ch}};
      break;
    case '*':
      token = Token{TokenType::Asterisk, std::string{m_ch}};
      break;
    case '<':
      token = Token{TokenType::LT, std::string{m_ch}};
      break;
    case '>':
      token = Token{TokenType::GT, std::string{m_ch}};
      break;
    case '\0':
      token = Token{TokenType::EoF, {}};
      break;
    default:
      if (utils::isAsciiLetter(m_ch)) {
        const auto literal = ReadIdentifier();
        const auto type = lookupIdent(literal);

        return Token{type, literal};
      }

      if (utils::isAsciiDigit(m_ch)) {
        return Token{TokenType::Int, ReadNumber()};
      }

      token = Token{TokenType::Illegal, {}};
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

  while (utils::isAsciiDigit(m_ch)) {
    ReadChar();
  }

  return m_input.substr(position, m_position - position);
}

auto Lexer::ReadIdentifier() -> std::string {
  const auto posiiton = m_position;
  auto num_chars = 0;

  while (utils::isAsciiLetter(m_ch)) {
    ReadChar();
    num_chars++;
  }

  return m_input.substr(posiiton, num_chars);
}

auto Lexer::PeekChar() -> char {
  if (m_read_position >= m_input.size()) {
    return '\0';
  }

  return m_input[m_read_position];
}

auto Lexer::SkipWhitespace() -> void {
  while (utils::isAsciiWhitespace(m_ch)) {
    ReadChar();
  }
}

}// namespace lexer
