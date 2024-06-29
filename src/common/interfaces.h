#pragma once

#include <sstream>

class Debug {
 public:
  virtual ~Debug() = default;
  virtual auto debug_print(std::ostream&) const -> void = 0;

  [[nodiscard]] auto to_debug_string() const -> std::string {
    std::ostringstream oss;
    debug_print(oss);
    return oss.str();
  }
};

template<typename T>
  requires std::is_base_of_v<Debug, T>
std::ostream& operator<<(std::ostream& os, const T& obj) {
  obj.debug_print(os);
  return os;
}
