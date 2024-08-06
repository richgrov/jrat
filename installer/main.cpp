#include <iostream>
#include <string>
#include <vector>

#include <Windows.h>

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

    std::cout << "handle is " << menu_key << "\n";
    return 0;
}
