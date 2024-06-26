#include "ast.h"
#include "integer_literal.h"
#include "let_statement.h"
#include "parser.h"
#include "return_statement.h"

#include <expression_statement.h>
#include <gtest/gtest.h>
#include <iostream>

// ── Utility function ────────────────────────────────────────────────

auto check_parser_errors(const ast::Parser& parser) -> void {
  const auto& errors = parser.errors();

  if (errors.empty()) return;

  for (const auto& err : errors) {
    FAIL() << "Parser error: " << err << std::endl;
  }
}

// ── Let statements ──────────────────────────────────────────────────

auto test_let_statement(ast::Statement* statement, const std::string& name) -> void {
  EXPECT_NE(statement, nullptr);
  EXPECT_EQ(statement->token_literal(), "let");

  auto let_statement = dynamic_cast<ast::LetStatement*>(statement);

  EXPECT_EQ(let_statement->name().value(), name);
  EXPECT_EQ(let_statement->name().token_literal(), name);
}

TEST(Parser, LetStatement) {
  const auto input = R"(
    let x = 5;
    let y = 10;
    let foobar = 838383;
  )";

  auto parser = ast::Parser{input};
  auto program = parser.parse_program();

  check_parser_errors(parser);

  const auto& statements = program.statements();

  EXPECT_EQ(statements.size(), 3);

  struct Test {
    std::string expected_identifier;
  };

  std::vector<Test> tests{
      {"x"},
      {"y"},
      {"foobar"},
  };

  for (size_t i = 0; i < tests.size(); ++i) {
    auto statement = statements[i].get();
    test_let_statement(statement, tests[i].expected_identifier);
  }
}

// ── Return statements ───────────────────────────────────────────────

TEST(Parser, ReturnStatement) {
  const auto input = R"(
    return 5;
    return 10;
    return 993322;
  )";

  auto parser = ast::Parser{input};
  auto program = parser.parse_program();
  const auto& statements = program.statements();

  check_parser_errors(parser);

  EXPECT_EQ(statements.size(), 3);

  for (auto& stmt : statements) {
    auto return_stmt = dynamic_cast<ast::ReturnStatement*>(stmt.get());

    EXPECT_NE(return_stmt, nullptr);
    EXPECT_EQ(return_stmt->token_literal(), "return");
  }
}

TEST(Parser, ToDebugString) {
  auto ident = ast::Identifier{Token{TokenType::Ident, "anotherVal"}, "anotherVar"};
}

//  ── Identifier expression ───────────────────────────────────────────

TEST(Parser, IdentifierExpression) {
  const auto input = "foobar;";

  auto parser = ast::Parser{input};
  auto program = parser.parse_program();
  check_parser_errors(parser);

  const auto& statements = program.statements();
  EXPECT_EQ(statements.size(), 1);

  const auto expr = dynamic_cast<ast::ExpressionStatement*>(statements[0].get());
  EXPECT_NE(expr, nullptr);

  const auto& ident = dynamic_cast<ast::Identifier&>(expr->value());
  EXPECT_EQ(ident.value(), "foobar");
  EXPECT_EQ(ident.token_literal(), "foobar");
}

TEST(Parser, IntegerExpression) {
  const auto input = "5;";

  auto parser = ast::Parser{input};
  auto program = parser.parse_program();
  check_parser_errors(parser);

  const auto& statements = program.statements();
  EXPECT_EQ(statements.size(), 1);

  const auto expr = dynamic_cast<ast::ExpressionStatement*>(statements[0].get());
  EXPECT_NE(expr, nullptr);

  const auto& int_literal = dynamic_cast<ast::IntegerLiteral&>(expr->value());
  EXPECT_EQ(int_literal.value(), 5);
  EXPECT_EQ(int_literal.token_literal(), "5");
}
