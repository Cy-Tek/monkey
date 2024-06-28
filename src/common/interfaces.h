#pragma once

class Debug {
 public:
  virtual ~Debug() = default;
  virtual auto DebugPrint(std::ostream&) const -> void = 0;
};

template<typename T>
  requires std::is_base_of_v<Debug, T>
std::ostream& operator<<(std::ostream& os, const T& obj) {
  obj.DebugPrint(os);
  return os;
}
