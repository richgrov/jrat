#pragma once
#include <string>

bool endsWith(std::string string, std::string end) {
    if (end.length() > string.length()) {
        return false;
    }

    return string.compare(string.size() - end.size(), end.size(), end) == 0;
}

std::string toLowercase(const std::string &string) {
    std::string lowercase = "";

    for (char c : string) {
        lowercase += std::tolower(c); // why can't this take an std::string?
    }

    return lowercase;
}