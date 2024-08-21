#include "registry_key.h"

#include <cstdlib>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <Windows.h>

using namespace jrat;

const RegistryKey RegistryKey::CLASSES_ROOT = RegistryKey(HKEY_CLASSES_ROOT);
const RegistryKey RegistryKey::LOCAL_MACHINE = RegistryKey(HKEY_LOCAL_MACHINE);

RegistryKey::RegistryKey(const RegistryKey &parent, const std::string &child) {
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
    LSTATUS result = RegCloseKey(reinterpret_cast<HKEY>(key_));
    if (result != ERROR_SUCCESS) {
        std::cerr << std::format("failed to close key: {}", result) << '\n';
        std::abort();
    }
}

std::string RegistryKey::get_string(const std::string &name) const {
    DWORD size;
    LSTATUS size_result = RegGetValue(
        reinterpret_cast<HKEY>(key_), nullptr, name.c_str(), RRF_RT_REG_SZ, nullptr, nullptr, &size
    );

    if (size_result != ERROR_SUCCESS) {
        throw std::runtime_error(
            std::format("failed to get size of registry value {}: {}", name, size_result)
        );
    }

    std::vector<char> buf;
    buf.resize(size + 1, ' '); // +1 for null terminator not being accounted for in all cases
    size = static_cast<DWORD>(buf.size());

    LSTATUS read_result = RegGetValue(
        reinterpret_cast<HKEY>(key_), nullptr, name.c_str(), RRF_RT_REG_SZ, nullptr, buf.data(),
        &size
    );

    if (read_result != ERROR_SUCCESS) {
        throw std::runtime_error(
            std::format("failed to read registry value {}: {}", name, read_result)
        );
    }

    return std::string(buf.data());
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

void RegistryKey::delete_child(const std::string &child) {
    LSTATUS res = RegDeleteTree(reinterpret_cast<HKEY>(key_), child.c_str());
    if (res != ERROR_SUCCESS) {
        throw std::runtime_error(std::format("failed to delete registry child {}: {}", child, res));
    }
}
