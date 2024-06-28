#pragma once

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

auto lookupIdent(const std::string& ident) -> TokenType;

auto operator<<(std::ostream& os, TokenType token_type) -> std::ostream&;

template<>
struct std::formatter<TokenType> {
  constexpr auto parse(std::format_parse_context& ctx) {
    // No specific format options to parse in this example.
    return ctx.begin();
  }

  auto format(TokenType t, std::format_context& ctx) {
    std::string name;
    switch (t) {
      case TokenType::Illegal: name = "Illegal"; break;
      case TokenType::EoF: name = "EoF"; break;
      case TokenType::Ident: name = "Ident"; break;
      case TokenType::Int: name = "Int"; break;
      case TokenType::Assign: name = "Assign"; break;
      case TokenType::Plus: name = "Plus"; break;
      case TokenType::Minus: name = "Minus"; break;
      case TokenType::Bang: name = "Bang"; break;
      case TokenType::Asterisk: name = "Asterisk"; break;
      case TokenType::Slash: name = "Slash"; break;
      case TokenType::LT: name = "LT"; break;
      case TokenType::GT: name = "GT"; break;
      case TokenType::EQ: name = "EQ"; break;
      case TokenType::NotEq: name = "NotEq"; break;
      case TokenType::Comma: name = "Comma"; break;
      case TokenType::Semicolon: name = "Semicolon"; break;
      case TokenType::LParen: name = "LParen"; break;
      case TokenType::RParen: name = "RParen"; break;
      case TokenType::LBrace: name = "LBrace"; break;
      case TokenType::RBrace: name = "RBrace"; break;
      case TokenType::Function: name = "Function"; break;
      case TokenType::Let: name = "Let"; break;
      case TokenType::True: name = "True"; break;
      case TokenType::False: name = "False"; break;
      case TokenType::If: name = "If"; break;
      case TokenType::Else: name = "Else"; break;
      case TokenType::Return: name = "Return"; break;
    }
    // Write the string to the format context's output iterator.
    return std::format_to(ctx.out(), "{}", name);
  }
};

class Token {
 public:
  Token();
  Token(TokenType type, std::string literal);

  Token(Token &&other) noexcept;
  auto operator=(Token &&other) noexcept -> Token &;

  Token(Token const &other) = default;
  auto operator=(Token const &other) -> Token & = default;

  [[nodiscard]] auto Type() const -> TokenType;
  [[nodiscard]] auto Literal() const -> const std::string &;

 private:
  TokenType m_type;
  std::string m_literal;
};
