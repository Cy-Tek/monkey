#pragma once

#include <ostream>

enum class TokenType {
  Illegal,
  EoF,

  // ╭────────────────────────╮
  // │ Identifiers + literals │
  // ╰────────────────────────╯

  Ident,
  Int,

  // ╭───────────╮
  // │ Operators │
  // ╰───────────╯

  Assign,
  Plus,

  // ╭────────────╮
  // │ Delimiters │
  // ╰────────────╯

  Comma,
  Semicolon,
  LParen,
  RParen,
  LBrace,
  RBrace,

  // ╭──────────╮
  // │ Keywords │
  // ╰──────────╯

  Function,
  Let
};

auto operator<<(std::ostream &os, TokenType token_type) -> std::ostream &;

class Token {
 public:
  Token() = delete;
  Token(TokenType type, std::string literal);

  auto Type() const -> TokenType;
  auto Literal() const -> const std::string &;

 private:
  TokenType m_type;
  std::string m_literal;
};
