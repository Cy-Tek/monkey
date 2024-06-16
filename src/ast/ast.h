#pragma once

namespace ast {

class Node {
 public:
  Node(const Node &) = delete;

  auto operator=(const Node &) -> Node & = delete;

  virtual ~Node() = default;

  [[nodiscard]] virtual auto tokenLiteral() const -> std::string = 0;
};

class Statement : public Node {
 public:
  Statement(const Statement &) = delete;

  auto operator=(const Statement &) -> Statement & = delete;

  ~Statement() override = default;
};

class Expression : public Node {
 public:
  Expression(const Expression &) = delete;

  auto operator=(const Expression &) -> Expression & = delete;

  ~Expression() override = default;
};

} // namespace ast
