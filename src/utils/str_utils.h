namespace utils {

/**
* @param ch - The character to test
* @return - Whether the char is a valid alphabetic value from a-z or A-Z
*/
auto isAsciiLetter(char ch) -> bool;

/**
* @param ch - The character to test
* @return - Whether the char is a valid ascii whitespace character
*/
auto isAsciiWhitespace(char ch) -> bool;

/**
* @param ch - The character to test
* @return - Whether the char is a valid ascii whitespace digit
*/
auto isAsciiDigit(char ch) -> bool;

auto trimLeft(std::string &str) -> void;
auto trimRight(std::string &str) -> void;
auto trim(std::string &str) -> void;

}// namespace utils
