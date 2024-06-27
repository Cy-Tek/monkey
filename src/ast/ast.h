#pragma once

namespace ast {

class Node {
 public:
  Node() = default;
  virtual ~Node() = default;

  Node(Node &&) noexcept = default;
  Node &operator=(Node &&) noexcept = default;

  Node(const Node &) = delete;
  auto operator=(const Node &) -> Node & = delete;

  [[nodiscard]] virtual auto TokenLiteral() const -> std::string = 0;
};

class Statement : public Node {
 public:
  Statement() = default;
  ~Statement() override = default;

  Statement(Statement &&) noexcept = default;
  Statement &operator=(Statement &&) noexcept = default;

  Statement(const Statement &) = delete;
  auto operator=(const Statement &) -> Statement & = delete;
};

class Expression : public Node {
 public:
  Expression() = default;
  ~Expression() override = default;

  Expression(Expression &&) noexcept = default;
  Expression &operator=(Expression &&) noexcept = default;

  Expression(const Expression &) = delete;
  auto operator=(const Expression &) -> Expression & = delete;
};

}// namespace ast
