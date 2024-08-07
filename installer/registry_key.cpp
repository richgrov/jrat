#include "registry_key.h"

#include <format>
#include <stdexcept>
#include <string>

#include <Windows.h>

using namespace jrat;

RegistryKey::RegistryKey(HKEY parent, const std::string &child) {
    LSTATUS result = RegCreateKeyEx(
        HKEY_CLASSES_ROOT, child.c_str(), 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &key_, nullptr
    );

    if (result != ERROR_SUCCESS) {
        throw std::runtime_error(
            std::format("failed to open/create registry key for child {}: error {}", child, result)
        );
    }
}

void RegistryKey::set_string(const std::string &name, const std::string &value) const {
    LSTATUS res = RegSetValueEx(
        key_, name.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE *>(value.c_str()),
        value.size() + 1
    );

    if (res != ERROR_SUCCESS) {
        throw std::runtime_error(
            std::format("failed to set registry {} to {}: error {}", name, value, res)
        );
    }
}
