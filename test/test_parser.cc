#include "ast.h"
#include "expression_statement.h"
#include "integer_literal.h"
#include "let_statement.h"
#include "parser.h"
#include "prefix_expression.h"
#include "return_statement.h"

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

//  ── Expressions tests ───────────────────────────────────────────────

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

  const auto stmt = dynamic_cast<ast::ExpressionStatement*>(statements[0].get());
  EXPECT_NE(stmt, nullptr);

  const auto& int_literal = dynamic_cast<ast::IntegerLiteral&>(stmt->value());
  EXPECT_EQ(int_literal.value(), 5);
  EXPECT_EQ(int_literal.token_literal(), "5");
}

TEST(Parser, PrefixExpressions) {
  struct Test {
    std::string input;
    std::string prefix_operator;
    int64_t integer_value;
  };

  const auto tests = std::vector<Test>{
      {"!5;", "!", 5},
      {"-15;", "-", 15},
  };

  for (const auto& test : tests) {
    auto parser = ast::Parser{test.input};
    auto program = parser.parse_program();
    check_parser_errors(parser);

    const auto& statements = program.statements();
    EXPECT_EQ(statements.size(), 1);

    const auto stmt = dynamic_cast<ast::ExpressionStatement*>(statements[0].get());
    EXPECT_NE(stmt, nullptr);

    const auto& expr = dynamic_cast<ast::PrefixExpression&>(stmt->value());
    EXPECT_EQ(expr.op(), test.prefix_operator);

    auto& int_literal = dynamic_cast<const ast::IntegerLiteral&>(expr.right());
    EXPECT_EQ(int_literal.value(), test.integer_value);
    EXPECT_EQ(int_literal.token_literal(), std::format("{}", test.integer_value));
  }
}

TEST(Parser, InfixExpressions) {
  struct Test {
    std::string input;
    uint64_t left_value;
    std::string op;
    uint64_t right_value;
  };

  const auto tests = std::vector<Test>{
      {"5 + 5;", 5, "+", 5},
      {"5 - 5;", 5, "-", 5},
      {"5 * 5;", 5, "*", 5},
      {"5 / 5;", 5, "/", 5},
      {"5 > 5;", 5, ">", 5},
      {"5 < 5;", 5, "<", 5},
      {"5 == 5;", 5, "==", 5},
      {"5 != 5;", 5, "!=", 5},
  };

  for (const auto& test : tests) {
    auto parser = ast::Parser{test.input};
    auto program = parser.parse_program();
    check_parser_errors(parser);

    auto& statements = program.statements();
    ASSERT_EQ(statements.size(), 1);
  }
}

TEST(Parser, OperatorPrecedenceParsing) {
  struct Test {
    std::string input;
    std::string expected;
  };

  const auto tests = std::vector<Test>{
      {"-a * b", "((-a) * b)"},
      {"!-a", "(!(-a))"},
      {"a + b + c", "((a + b) + c)"},
      {"a + b - c", "((a + b) - c)"},
      {"a * b * c", "((a * b) * c)"},
      {"a * b / c", "((a * b) / c)"},
      {"a + b / c", "(a + (b / c))"},
      {"a + b * c + d / e - f", "(((a + (b * c)) + (d / e)) - f)"},
      {"3 + 4; -5 * 5", "(3 + 4)((-5) * 5)"},
      {"5 > 4 == 3 < 4", "((5 > 4) == (3 < 4))"},
      {"5 < 4 != 3 > 4", "((5 < 4) != (3 > 4))"},
      {"3 + 4 * 5 == 3 * 1 + 4 * 5", "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))"},
  };

  auto ss = std::ostringstream{};
  for (const auto& test : tests) {
    auto parser = ast::Parser(test.input);
    auto program = parser.parse_program();
    check_parser_errors(parser);

    program.debug_print(ss);
    EXPECT_EQ(ss.str(), test.expected);

    ss.str("");// reset the string stream to have no input
  }
}
