#pragma once

namespace ast {

class Node {
 public:
  Node(const Node &) = delete;
  auto operator=(const Node &) -> Node & = delete;

  Node() = default;
  virtual ~Node() = default;

  [[nodiscard]] virtual auto TokenLiteral() const -> std::string = 0;
};

class Statement : public Node {
 public:
  Statement(const Statement &) = delete;
  auto operator=(const Statement &) -> Statement & = delete;

  Statement() = default;
  ~Statement() override = default;
};

class Expression : public Node {
 public:
  Expression(const Expression &) = delete;
  auto operator=(const Expression &) -> Expression & = delete;

  Expression() = default;
  ~Expression() override = default;
};

}// namespace ast
