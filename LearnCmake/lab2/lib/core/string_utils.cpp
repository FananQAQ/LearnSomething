#include "string_utils.h"

#include <cctype>
#include <sstream>
#include <algorithm>

namespace {

bool is_space(unsigned char ch) {
    return std::isspace(ch) != 0;
}

}  // namespace

std::string trim(const std::string& text) {
    std::size_t begin = 0;
    while (begin < text.size() && is_space(static_cast<unsigned char>(text[begin]))) {
        ++begin;
    }

    std::size_t end = text.size();
    while (end > begin && is_space(static_cast<unsigned char>(text[end - 1]))) {
        --end;
    }

    return text.substr(begin, end - begin);
}

std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> parts;
    std::stringstream stream(text);
    std::string item;

    while (std::getline(stream, item, delimiter)) {
        const std::string piece = trim(item);
        if (!piece.empty()) {
            parts.push_back(piece);
        }
    }

    return parts;
}

std::string to_upper(const std::string& text) {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::size_t count_words(const std::string& text, char delimiter) {
    return split(text, delimiter).size();
}
