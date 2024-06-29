#pragma once

class Token;

namespace lexer {

class Lexer {
 public:
  Lexer() = delete;
  explicit Lexer(std::string input);

  Lexer(const Lexer&) = delete;
  Lexer(Lexer&&) = delete;
  auto operator=(const Lexer&) -> Lexer& = delete;
  auto operator=(Lexer&&) -> Lexer& = delete;

  auto next_token() -> Token;

 private:
  std::string m_input;
  size_t m_position = 0;
  size_t m_read_position = 0;
  char m_ch = 0;

  auto read_char() -> void;
  auto read_number() -> std::string;
  auto read_identifier() -> std::string;

  [[nodiscard]] auto peek_char() const -> char;

  auto skip_whitespace() -> void;
};

}// namespace lexer
