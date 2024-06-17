auto isAsciiLetter(char ch) -> bool {
  auto is_lowercase = ch >= 'a' && ch <= 'z';
  auto is_uppercase = ch >= 'A' && ch <= 'Z';

  return is_lowercase || is_uppercase;
}

auto isAsciiWhitespace(char ch) -> bool {
  return ch == '\t' || ch == ' ' || ch == '\r' || ch == '\n';
}

auto isAsciiDigit(char ch) -> bool {
  return ch >= '0' && ch <= '9';
}
