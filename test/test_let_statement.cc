#include "ast.h"
#include "let_statement.h"
#include "parser.h"

#include <gtest/gtest.h>

auto testLetStatement(ast::Statement* statement, const std::string &name) -> void {
  EXPECT_NE(statement, nullptr);
  EXPECT_EQ(statement->TokenLiteral(), "let");

  auto let_statement = dynamic_cast<ast::LetStatement *>(statement);

  EXPECT_EQ(let_statement->Name().Value(), name);
  EXPECT_EQ(let_statement->Name().TokenLiteral(), name);
}

TEST(LetStatement, IntAssignment) {
  const auto input = R"(
    let x = 5;
    let y = 10;
    let foobar = 838383;
  )";

  auto parser = ast::Parser{input};
  auto program = parser.ParseProgram();
  const auto &statements = program.Statements();

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
    testLetStatement(statement, tests[i].expected_identifier);
  }
}
