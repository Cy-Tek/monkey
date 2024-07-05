#include "lexer.h"
#include "token.h"

#include "str_utils.h"

namespace lexer {

Lexer::Lexer(std::string input) : m_input{std::move(input)} {
  read_char();
}

auto Lexer::next_token() -> Token {
  std::optional<Token> token{};

  skip_whitespace();

  switch (m_ch) {
  case '=':
    if (peek_char() == '=') {
      read_char();
      token = Token{TokenType::EQ, "=="};
    } else {
      token = Token{TokenType::Assign, std::string{m_ch}};
    }

    break;
  case ';': token = Token{TokenType::Semicolon, std::string{m_ch}}; break;
  case ',': token = Token{TokenType::Comma, std::string{m_ch}}; break;
  case '(': token = Token{TokenType::LParen, std::string{m_ch}}; break;
  case ')': token = Token{TokenType::RParen, std::string{m_ch}}; break;
  case '{': token = Token{TokenType::LBrace, std::string{m_ch}}; break;
  case '}': token = Token{TokenType::RBrace, std::string{m_ch}}; break;
  case '+': token = Token{TokenType::Plus, std::string{m_ch}}; break;
  case '-': token = Token{TokenType::Minus, std::string{m_ch}}; break;
  case '!':
    if (peek_char() == '=') {
      read_char();
      token = Token{TokenType::NotEq, "!="};
    } else {
      token = Token{TokenType::Bang, std::string{m_ch}};
    }

    break;
  case '/': token = Token{TokenType::Slash, std::string{m_ch}}; break;
  case '*': token = Token{TokenType::Asterisk, std::string{m_ch}}; break;
  case '<': token = Token{TokenType::LT, std::string{m_ch}}; break;
  case '>': token = Token{TokenType::GT, std::string{m_ch}}; break;
  case '\0': token = Token{TokenType::EoF, {}}; break;
  default:
    if (utils::is_ascii_letter(m_ch)) {
      const auto literal = read_identifier();
      const auto type    = lookupIdent(literal);

      return Token{type, literal};
    }

    if (utils::is_ascii_digit(m_ch)) {
      return Token{TokenType::Int, read_number()};
    }

    token = Token{TokenType::Illegal, {}};
  };

  read_char();
  return *token;
}

auto Lexer::read_char() -> void {
  if (m_read_position >= m_input.size()) {
    m_ch = 0;
  } else {
    m_ch = m_input[m_read_position];
  }

  m_position = m_read_position;
  m_read_position++;
}

auto Lexer::read_number() -> std::string {
  auto position = m_position;

  while (utils::is_ascii_digit(m_ch)) { read_char(); }

  return m_input.substr(position, m_position - position);
}

auto Lexer::read_identifier() -> std::string {
  const auto position  = m_position;
  auto       num_chars = 0;

  while (utils::is_ascii_letter(m_ch)) {
    read_char();
    num_chars++;
  }

  return m_input.substr(position, num_chars);
}

auto Lexer::peek_char() const -> char {
  if (m_read_position >= m_input.size()) { return '\0'; }

  return m_input[m_read_position];
}

auto Lexer::skip_whitespace() -> void {
  while (utils::is_ascii_whitespace(m_ch)) { read_char(); }
}

} // namespace lexer
