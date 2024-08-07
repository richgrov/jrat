#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <Windows.h>

void registry_set(HKEY key, const std::string &name, const std::string &value) {
    LSTATUS res = RegSetValueEx(
        key, name.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE *>(value.c_str()),
        value.size() + 1
    );

    if (res != ERROR_SUCCESS) {
        throw std::runtime_error(
            std::format("failed to set registry key to {}: error {}", value, res)
        );
    }
}

int main(int argc, char **argv) {
    std::vector<std::string> file_types = {".png", ".jpeg"};

    HKEY menu_key;
    LSTATUS result = RegCreateKeyEx(
        HKEY_CLASSES_ROOT, "*\\shell\\jrat", 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &menu_key,
        nullptr
    );

    if (result != ERROR_SUCCESS) {
        std::cerr << "failed to get registry handle: " << result << "\n";
        return -1;
    }

    registry_set(menu_key, "MUIVerb", "JRAT");
    return 0;
}
