#pragma once

#include <ostream>

enum class TokenType {
  Illegal,
  EoF,

  // ── Identifiers + literals ──────────────────────────────────────────

  Ident,
  Int,

  // ── Operators ───────────────────────────────────────────────────────

  Assign,
  Plus,
  Minus,
  Bang,
  Asterisk,
  Slash,

  LT,
  GT,
  EQ,
  NotEq,

  // ── Delimiters ──────────────────────────────────────────────────────

  Comma,
  Semicolon,

  LParen,
  RParen,
  LBrace,
  RBrace,

  // ── Keywords ────────────────────────────────────────────────────────

  Function,
  Let,
  True,
  False,
  If,
  Else,
  Return,
};

auto operator<<(std::ostream &os, TokenType token_type) -> std::ostream &;
auto lookupIdent(const std::string &ident) -> TokenType;

class Token {
 public:
  Token() = delete;
  Token(TokenType type, std::string literal);
  Token(Token &&other);

  auto Type() const -> TokenType;
  auto Literal() const -> const std::string &;

 private:
  TokenType m_type;
  std::string m_literal;
};
