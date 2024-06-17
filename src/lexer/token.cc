#include "token.h"

static const std::map<std::string, TokenType> keywords = {
    {"fn", TokenType::Function},
    {"let", TokenType::Let},
};

auto lookupIdent(const std::string &ident) -> TokenType {
  if (auto it = keywords.find(ident); it != keywords.end()) {
    return it->second;
  }

  return TokenType::Ident;
}

Token::Token(TokenType type, std::string literal) : m_type{type}, m_literal{std::move(literal)} {}

auto Token::Type() const -> TokenType {
  return m_type;
}
auto Token::Literal() const -> const std::string & {
  return m_literal;
}

auto tokenTypeToString(TokenType type) -> std::string {
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
  }
}

auto operator<<(std::ostream &os, TokenType token_type) -> std::ostream & {
  return os << tokenTypeToString(token_type);
}
