#include "lexer.h"
#include "token.h"

#include <gtest/gtest.h>

TEST(Lexer, NextToken) {
  using namespace lexer;

  const auto input = R"(
    let five = 5;
    let ten = 10;

    let add = fn(x, y) {
      x + y;
    };

    let result = add(five, ten);
    !-/*5;
    5 < 10 > 5;

    if (5 < 10) {
      return true;
    } else {
      return false;
    }

    10 == 10;
    10 != 9;
  )";

  struct Test {
    TokenType   expected_type;
    std::string expected_literal;
  };

  std::vector<Test> tests{
      {TokenType::Let, "let"},       {TokenType::Ident, "five"},
      {TokenType::Assign, "="},      {TokenType::Int, "5"},

      {TokenType::Semicolon, ";"},   {TokenType::Let, "let"},
      {TokenType::Ident, "ten"},     {TokenType::Assign, "="},
      {TokenType::Int, "10"},        {TokenType::Semicolon, ";"},

      {TokenType::Let, "let"},       {TokenType::Ident, "add"},
      {TokenType::Assign, "="},      {TokenType::Function, "fn"},
      {TokenType::LParen, "("},      {TokenType::Ident, "x"},
      {TokenType::Comma, ","},       {TokenType::Ident, "y"},
      {TokenType::RParen, ")"},      {TokenType::LBrace, "{"},

      {TokenType::Ident, "x"},       {TokenType::Plus, "+"},
      {TokenType::Ident, "y"},       {TokenType::Semicolon, ";"},

      {TokenType::RBrace, "}"},      {TokenType::Semicolon, ";"},

      {TokenType::Let, "let"},       {TokenType::Ident, "result"},
      {TokenType::Assign, "="},      {TokenType::Ident, "add"},
      {TokenType::LParen, "("},      {TokenType::Ident, "five"},
      {TokenType::Comma, ","},       {TokenType::Ident, "ten"},
      {TokenType::RParen, ")"},      {TokenType::Semicolon, ";"},

      {TokenType::Bang, "!"},        {TokenType::Minus, "-"},
      {TokenType::Slash, "/"},       {TokenType::Asterisk, "*"},
      {TokenType::Int, "5"},         {TokenType::Semicolon, ";"},

      {TokenType::Int, "5"},         {TokenType::LT, "<"},
      {TokenType::Int, "10"},        {TokenType::GT, ">"},
      {TokenType::Int, "5"},         {TokenType::Semicolon, ";"},

      {TokenType::If, "if"},         {TokenType::LParen, "("},
      {TokenType::Int, "5"},         {TokenType::LT, "<"},
      {TokenType::Int, "10"},        {TokenType::RParen, ")"},
      {TokenType::LBrace, "{"},

      {TokenType::Return, "return"}, {TokenType::True, "true"},
      {TokenType::Semicolon, ";"},

      {TokenType::RBrace, "}"},      {TokenType::Else, "else"},
      {TokenType::LBrace, "{"},

      {TokenType::Return, "return"}, {TokenType::False, "false"},
      {TokenType::Semicolon, ";"},

      {TokenType::RBrace, "}"},

      {TokenType::Int, "10"},        {TokenType::EQ, "=="},
      {TokenType::Int, "10"},        {TokenType::Semicolon, ";"},

      {TokenType::Int, "10"},        {TokenType::NotEq, "!="},
      {TokenType::Int, "9"},         {TokenType::Semicolon, ";"},

      {TokenType::EoF, "\0"},
  };

  auto lexer = Lexer{input};

  for (const auto& [expected_type, expected_literal] : tests) {
    const auto token = lexer.next_token();

    EXPECT_EQ(token.type(), expected_type);
    EXPECT_EQ(token.literal(), expected_literal);
  }
}
