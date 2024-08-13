#include <format>
#include <span>
#include <stdexcept>
#include <string>

#include <Windows.h> // IWYU pragma: export

#include "resources.h"

using namespace jrat;

std::span<unsigned char> jrat::get_resource(const std::string &id) {
    HMODULE module = GetModuleHandle(nullptr);
    HRSRC res_info = FindResource(module, id.c_str(), "DATA");
    if (res_info == nullptr) {
        throw std::runtime_error(std::format("couldn't find resource {}: {}", id, GetLastError()));
    }

    HGLOBAL res = LoadResource(module, res_info);
    if (res == nullptr) {
        throw std::runtime_error(std::format("couldn't load resource {}: {}", id, GetLastError()));
    }

    void *data = LockResource(res);
    if (data == nullptr) {
        throw std::runtime_error(std::format("failed to lock resource {}", id));
    }

    DWORD size = SizeofResource(module, res_info);
    if (size == 0) {
        throw std::runtime_error(
            std::format("couldn't get size of resource {}: {}", id, GetLastError())
        );
    }

    return std::span(reinterpret_cast<unsigned char *>(data), size);
}
