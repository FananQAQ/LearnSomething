#ifndef LAB2_STRING_UTILS_H
#define LAB2_STRING_UTILS_H

#include <string>
#include <vector>

std::string trim(const std::string& text);
std::vector<std::string> split(const std::string& text, char delimiter);
std::size_t count_words(const std::string& text, char delimiter);

std::string to_upper(const std::string& text);

#endif
