#include "str_utils.h"

namespace utils {

auto isAsciiLetter(char ch) -> bool {
  const auto is_lowercase = ch >= 'a' && ch <= 'z';
  const auto is_uppercase = ch >= 'A' && ch <= 'Z';

  return is_lowercase || is_uppercase;
}

auto isAsciiWhitespace(char ch) -> bool {
  return ch == '\t' || ch == ' ' || ch == '\r' || ch == '\n';
}

auto isAsciiDigit(char ch) -> bool {
  return ch >= '0' && ch <= '9';
}

auto trimLeft(std::string &str) -> void {
  str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
              return !std::isspace(ch);
            }));
}

auto trimRight(std::string &str) -> void {
  str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
              return !std::isspace(ch);
            }).base(),
            str.end());
}

auto trim(std::string &str) -> void {
  trimLeft(str);
  trimRight(str);
}

}// namespace utils
