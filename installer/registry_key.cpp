#include "registry_key.h"

#include <format>
#include <stdexcept>
#include <string>

#include <Windows.h>

using namespace jrat;

const RegistryKey RegistryKey::CLASSES_ROOT = RegistryKey(HKEY_CLASSES_ROOT);

RegistryKey::RegistryKey(const RegistryKey parent, const std::string &child) {
    LSTATUS result = RegCreateKeyEx(
        reinterpret_cast<HKEY>(parent.key_), child.c_str(), 0, nullptr, 0, KEY_ALL_ACCESS, nullptr,
        reinterpret_cast<HKEY *>(&key_), nullptr
    );

    if (result != ERROR_SUCCESS) {
        throw std::runtime_error(
            std::format("failed to open/create registry key for child {}: error {}", child, result)
        );
    }
}

RegistryKey::~RegistryKey() {
    RegCloseKey(reinterpret_cast<HKEY>(key_));
}

void RegistryKey::set_string(const std::string &name, const std::string &value) const {
    LSTATUS res = RegSetValueEx(
        reinterpret_cast<HKEY>(key_), name.c_str(), 0, REG_SZ,
        reinterpret_cast<const BYTE *>(value.c_str()), static_cast<DWORD>(value.size() + 1)
    );

    if (res != ERROR_SUCCESS) {
        throw std::runtime_error(
            std::format("failed to set registry {} to {}: error {}", name, value, res)
        );
    }
}
