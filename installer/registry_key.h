#pragma once

#include <string>

namespace jrat {

class RegistryKey {
public:
    explicit RegistryKey(RegistryKey parent, const std::string &child);

    ~RegistryKey();

    void set_string(const std::string &name, const std::string &value) const;

    static const RegistryKey CLASSES_ROOT;

private:
    inline explicit RegistryKey(void *key) {
        key_ = key;
    }

    // HKEY type is erased to prevent leaking Windows.h file, which has definitions that conflict
    // with raylib.h
    void *key_;
};

} // namespace jrat
