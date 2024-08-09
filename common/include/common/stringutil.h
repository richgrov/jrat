#pragma once
#include <string>

namespace jrat {

std::string to_lowercase(const std::string &string) {
    std::string lowercase = "";

    for (char c : string) {
        lowercase += std::tolower(c); // why can't this take an std::string?
    }

    return lowercase;
}

} // namespace jrat