#pragma once

namespace utils {

/**
* @param ch - The character to test
* @return - Whether the char is a valid alphabetic value from a-z or A-Z
*/
auto is_ascii_letter(char ch) -> bool;

/**
* @param ch - The character to test
* @return - Whether the char is a valid ascii whitespace character
*/
auto is_ascii_whitespace(char ch) -> bool;

/**
* @param ch - The character to test
* @return - Whether the char is a valid ascii whitespace digit
*/
auto is_ascii_digit(char ch) -> bool;

auto trim_left(std::string& str) -> void;
auto trim_right(std::string& str) -> void;
auto trim(std::string& str) -> void;

}// namespace utils
