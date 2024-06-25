#pragma once

class Token;

namespace lexer {

class Lexer {
 public:
  Lexer() = delete;
  explicit Lexer(std::string input);

  Lexer(const Lexer &) = delete;
  Lexer(Lexer &&) = delete;
  Lexer &operator=(const Lexer &) = delete;
  Lexer &operator=(Lexer &&) = delete;

  auto NextToken() -> Token;

 private:
  std::string m_input;
  size_t m_position = 0;
  size_t m_read_position = 0;
  char m_ch = 0;

  auto ReadChar() -> void;
  auto ReadNumber() -> std::string;
  auto ReadIdentifier() -> std::string;

  auto PeekChar() -> char;

  auto SkipWhitespace() -> void;
};

}// namespace lexer
