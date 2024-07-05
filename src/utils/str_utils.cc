#include "str_utils.h"

namespace utils {

auto is_ascii_letter(char ch) -> bool {
  const auto is_lowercase = ch >= 'a' && ch <= 'z';
  const auto is_uppercase = ch >= 'A' && ch <= 'Z';

  return is_lowercase || is_uppercase;
}

auto is_ascii_whitespace(char ch) -> bool {
  return ch == '\t' || ch == ' ' || ch == '\r' || ch == '\n';
}

auto is_ascii_digit(char ch) -> bool {
  return ch >= '0' && ch <= '9';
}

auto trim_left(std::string& str) -> void {
  str.erase(str.begin(),
            std::find_if(str.begin(), str.end(),
                         [](unsigned char ch) { return !std::isspace(ch); }));
}

auto trim_right(std::string& str) -> void {
  str.erase(std::find_if(str.rbegin(), str.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            str.end());
}

auto trim(std::string& str) -> void {
  trim_left(str);
  trim_right(str);
}

} // namespace utils
