#pragma once

#include <span>
#include <string>

namespace jrat {

std::span<unsigned char> get_resource(const std::string &id);
  
} // namespace
