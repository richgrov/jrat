#pragma once

#include <string>

#include <Windows.h>
#include <winreg.h>

namespace jrat {

class RegistryKey {
public:
    explicit RegistryKey(HKEY parent, const std::string &child);

    inline ~RegistryKey() {
        RegCloseKey(key_);
    }

    void set_string(const std::string &name, const std::string &value) const;

private:
    HKEY key_;
};

} // namespace jrat
