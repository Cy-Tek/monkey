#pragma once

class Debug {
 public:
  virtual ~Debug() = default;
  virtual auto debug_print(std::ostream&) const -> void = 0;
};

template<typename T>
  requires std::is_base_of_v<Debug, T>
std::ostream& operator<<(std::ostream& os, const T& obj) {
  obj.debug_print(os);
  return os;
}
