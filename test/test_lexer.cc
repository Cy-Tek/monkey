#include "lexer.h"
#include "token.h"

#include <gtest/gtest.h>

struct NextTokenTest {
  TokenType expected_type;
  std::string expected_literal;
};

TEST(Lexer, NextToken) {
  using namespace lexer;

  const auto input = R"(
    let five = 5;
    let ten = 10;

    let add = fn(x, y) {
      x + y;
    };

    let result = add(five, ten);
  )";

  std::vector<NextTokenTest> tests{
      {TokenType::Let, "let"},
      {TokenType::Ident, "five"},
      {TokenType::Assign, "="},
      {TokenType::Int, "5"},

      {TokenType::Semicolon, ";"},
      {TokenType::Let, "let"},
      {TokenType::Ident, "ten"},
      {TokenType::Assign, "="},
      {TokenType::Int, "10"},
      {TokenType::Semicolon, ";"},

      {TokenType::Let, "let"},
      {TokenType::Ident, "add"},
      {TokenType::Assign, "="},
      {TokenType::Function, "fn"},
      {TokenType::LParen, "("},
      {TokenType::Ident, "x"},
      {TokenType::Comma, ","},
      {TokenType::Ident, "y"},
      {TokenType::RParen, ")"},
      {TokenType::LBrace, "{"},

      {TokenType::Ident, "x"},
      {TokenType::Plus, "+"},
      {TokenType::Ident, "y"},
      {TokenType::Semicolon, ";"},

      {TokenType::RBrace, "}"},
      {TokenType::Semicolon, ";"},

      {TokenType::Let, "let"},
      {TokenType::Ident, "result"},
      {TokenType::Assign, "="},
      {TokenType::Ident, "add"},
      {TokenType::LParen, "("},
      {TokenType::Ident, "five"},
      {TokenType::Comma, ","},
      {TokenType::Ident, "ten"},
      {TokenType::RParen, ")"},
      {TokenType::Semicolon, ";"},
      {TokenType::EoF, "\0"},
  };

  auto lexer = Lexer{input};

  for (const auto test : tests) {
    const auto token = lexer.NextToken();

    EXPECT_EQ(token.Type(), test.expected_type);
    EXPECT_EQ(token.Literal(), test.expected_literal);
  }
}
