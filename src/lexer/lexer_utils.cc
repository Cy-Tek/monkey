auto is_ascii_letter(char ch) -> bool {
  auto is_lowercase = ch >= 'a' && ch <= 'z';
  auto is_uppercase = ch >= 'A' && ch <= 'Z';

  return is_lowercase || is_uppercase;
}
