#include "ast.h"
#include "boolean_literal.h"
#include "expression_statement.h"
#include "infix_expression.h"
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

auto test_identifier(const ast::Expression& expr, std::string value) -> void {
  auto& ident = dynamic_cast<const ast::Identifier&>(expr);

  EXPECT_EQ(ident.value(), value);
  EXPECT_EQ(ident.token_literal(), value);
}

auto test_integer_literal(const ast::Expression& expr, int64_t value) -> void {
  auto& literal = dynamic_cast<const ast::IntegerLiteral&>(expr);

  EXPECT_EQ(literal.value(), value);
  EXPECT_EQ(literal.token_literal(), std::to_string(value));
}

auto test_bool_literal(const ast::Expression& expr, bool value) -> void {
  auto& literal = dynamic_cast<const ast::BooleanLiteral&>(expr);

  EXPECT_EQ(literal.value(), value);

  if (value)
    EXPECT_EQ(literal.token_literal(), "true");
  else
    EXPECT_EQ(literal.token_literal(), "false");
}

auto test_literal_expression(const ast::Expression& expr,
                             auto&&                 expected) -> void {
  using T = std::decay_t<decltype(expected)>;

  if constexpr (std::is_same_v<T, int>) {
    test_integer_literal(expr, static_cast<int64_t>(expected));
    return;
  } else if constexpr (std::is_same_v<T, int64_t>) {
    test_integer_literal(expr, expected);
    return;
  } else if constexpr (std::is_same_v<T, bool>) {
    test_bool_literal(expr, expected);
    return;
  } else if constexpr (std::is_same_v<T, std::string>(expected)) {
    test_identifier(expr, expected);
    return;
  }

  FAIL() << "Type of expr not handled: got " << typeid(T).name();
}

auto test_infix_expression(const ast::Expression& expression, auto&& left,
                           std::string op, auto&& right) -> void {
  const auto& expr = dynamic_cast<const ast::InfixExpression&>(expression);

  test_literal_expression(expr.left(), left);
  test_literal_expression(expr.right(), right);
  EXPECT_EQ(expr.op(), op);
}

// ── Let statements ──────────────────────────────────────────────────

auto test_let_statement(ast::Statement*    statement,
                        const std::string& name) -> void {
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

  auto parser  = ast::Parser{input};
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

  auto        parser     = ast::Parser{input};
  auto        program    = parser.parse_program();
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
  auto ident =
      ast::Identifier{Token{TokenType::Ident, "anotherVal"}, "anotherVar"};
}

//  ── Expressions tests ───────────────────────────────────────────────

TEST(Parser, IdentifierExpression) {
  const auto input = "foobar;";

  auto parser  = ast::Parser{input};
  auto program = parser.parse_program();
  check_parser_errors(parser);

  const auto& statements = program.statements();
  EXPECT_EQ(statements.size(), 1);

  const auto expr =
      dynamic_cast<ast::ExpressionStatement*>(statements[0].get());
  EXPECT_NE(expr, nullptr);

  const auto& ident = dynamic_cast<ast::Identifier&>(expr->value());
  EXPECT_EQ(ident.value(), "foobar");
  EXPECT_EQ(ident.token_literal(), "foobar");
}

TEST(Parser, IntegerExpression) {
  const auto input = "5;";

  auto parser  = ast::Parser{input};
  auto program = parser.parse_program();
  check_parser_errors(parser);

  const auto& statements = program.statements();
  EXPECT_EQ(statements.size(), 1);

  const auto stmt =
      dynamic_cast<ast::ExpressionStatement*>(statements[0].get());
  EXPECT_NE(stmt, nullptr);

  const auto& int_literal = dynamic_cast<ast::IntegerLiteral&>(stmt->value());
  EXPECT_EQ(int_literal.value(), 5);
  EXPECT_EQ(int_literal.token_literal(), "5");
}

TEST(Parser, PrefixExpressions) {
  struct Test {
    std::string input;
    std::string prefix_operator;
    int64_t     integer_value;
  };

  const auto tests = std::vector<Test>{
      {"!5;", "!", 5},
      {"-15;", "-", 15},
  };

  for (const auto& test : tests) {
    auto parser  = ast::Parser{test.input};
    auto program = parser.parse_program();
    check_parser_errors(parser);

    const auto& statements = program.statements();
    EXPECT_EQ(statements.size(), 1);

    const auto stmt =
        dynamic_cast<ast::ExpressionStatement*>(statements[0].get());
    EXPECT_NE(stmt, nullptr);

    const auto& expr = dynamic_cast<ast::PrefixExpression&>(stmt->value());
    EXPECT_EQ(expr.op(), test.prefix_operator);

    test_integer_literal(expr.right(), test.integer_value);
  }
}

TEST(Parser, InfixExpressions) {
  struct IntTest {
    std::string input;
    int64_t     left_value;
    std::string op;
    int64_t     right_value;
  };

  struct BoolTest {
    std::string input;
    bool        left_value;
    std::string op;
    bool        right_value;
  };

  const auto int_tests = std::vector<IntTest>{
      {"5 + 5;", 5, "+", 5},   {"5 - 5;", 5, "-", 5},   {"5 * 5;", 5, "*", 5},
      {"5 / 5;", 5, "/", 5},   {"5 > 5;", 5, ">", 5},   {"5 < 5;", 5, "<", 5},
      {"5 == 5;", 5, "==", 5}, {"5 != 5;", 5, "!=", 5},
  };

  const auto bool_tests = std::vector<BoolTest>{
      {"true == true", true, "==", true},
      {"true == false", true, "==", false},
      {"false == false", false, "==", false},
  };

  for (const auto& test : int_tests) {
    auto parser  = ast::Parser{test.input};
    auto program = parser.parse_program();
    check_parser_errors(parser);

    auto& statements = program.statements();
    ASSERT_EQ(statements.size(), 1);

    const auto stmt =
        dynamic_cast<ast::ExpressionStatement*>(statements[0].get());
    EXPECT_NE(stmt, nullptr);

    test_infix_expression(stmt->value(), test.left_value, test.op,
                          test.right_value);
  }

  for (const auto& test : bool_tests) {
    auto parser  = ast::Parser{test.input};
    auto program = parser.parse_program();
    check_parser_errors(parser);

    auto& statements = program.statements();
    ASSERT_EQ(statements.size(), 1);

    const auto stmt =
        dynamic_cast<ast::ExpressionStatement*>(statements[0].get());
    EXPECT_NE(stmt, nullptr);

    test_infix_expression(stmt->value(), test.left_value, test.op,
                          test.right_value);
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
      {"true", "true"},
      {"false", "false"},
      {"3 > 5 == false", "((3 > 5) == false)"},
      {"3 < 5 == true", "((3 < 5) == true)"},
  };

  auto ss = std::ostringstream{};
  for (const auto& test : tests) {
    auto parser  = ast::Parser(test.input);
    auto program = parser.parse_program();
    check_parser_errors(parser);

    ss << program;
    EXPECT_EQ(ss.str(), test.expected);

    ss.str(""); // reset the string stream to have no input
  }
}
