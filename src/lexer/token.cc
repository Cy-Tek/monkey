#include "token.h"

static const std::map<std::string, TokenType> keywords = {
    {"fn", TokenType::Function},
    {"let", TokenType::Let},
    {"true", TokenType::True},
    {"false", TokenType::False},
    {"if", TokenType::If},
    {"else", TokenType::Else},
    {"return", TokenType::Return},
};

auto lookupIdent(const std::string& ident) -> TokenType {
  if (auto it = keywords.find(ident); it != keywords.end()) {
    return it->second;
  }

  return TokenType::Ident;
}

Token::Token() : m_type{TokenType::Illegal}, m_literal{"\0"} {}
Token::Token(TokenType type, std::string literal) : m_type{type}, m_literal{std::move(literal)} {}

Token::Token(Token&& other) noexcept {
  if (this != &other) {
    m_type = other.m_type;
    other.m_type = TokenType::Illegal;

    m_literal = std::move(other.m_literal);
  }
}
auto Token::operator=(Token&& other) noexcept -> Token& {
  if (this != &other) {
    m_type = other.m_type;
    other.m_type = TokenType::Illegal;

    m_literal = std::move(other.m_literal);
  }

  return *this;
}

auto Token::Type() const -> TokenType {
  return m_type;
}

auto Token::Literal() const -> const std::string& {
  return m_literal;
}

auto tokenTypeToString(TokenType type) -> std::string_view {
  switch (type) {
    case TokenType::Illegal:
      return "ILLEGAL";
    case TokenType::EoF:
      return "EOF";
    case TokenType::Ident:
      return "IDENT";
    case TokenType::Int:
      return "INT";
    case TokenType::Assign:
      return "ASSIGN";
    case TokenType::Plus:
      return "PLUS";
    case TokenType::Minus:
      return "MINUS";
    case TokenType::Bang:
      return "BANG";
    case TokenType::Slash:
      return "SLASH";
    case TokenType::Asterisk:
      return "ASTERISK";
    case TokenType::LT:
      return "LT";
    case TokenType::GT:
      return "GT";
    case TokenType::EQ:
      return "EQ";
    case TokenType::NotEq:
      return "NOTEQ";
    case TokenType::Comma:
      return "COMMA";
    case TokenType::Semicolon:
      return "SEMICOLON";
    case TokenType::LParen:
      return "LPAREN";
    case TokenType::RParen:
      return "RPAREN";
    case TokenType::LBrace:
      return "LBRACE";
    case TokenType::RBrace:
      return "RBRACE";
    case TokenType::Function:
      return "FUNCTION";
    case TokenType::Let:
      return "LET";
    case TokenType::True:
      return "TRUE";
    case TokenType::False:
      return "FALSE";
    case TokenType::If:
      return "IF";
    case TokenType::Else:
      return "ELSE";
    case TokenType::Return:
      return "RETURN";
  }

  return "undefined";
}

auto operator<<(std::ostream& os, TokenType token_type) -> std::ostream& {
  return os << tokenTypeToString(token_type);
}
