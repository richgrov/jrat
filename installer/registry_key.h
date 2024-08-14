#pragma once

#include <string>

namespace jrat {

class RegistryKey {
public:
    explicit RegistryKey(const RegistryKey &parent, const std::string &child);

    ~RegistryKey();

    std::string get_string(const std::string &name) const;

    void set_string(const std::string &name, const std::string &value) const;

    static const RegistryKey CLASSES_ROOT;
    static const RegistryKey LOCAL_MACHINE;

private:
    inline explicit RegistryKey(void *key) {
        key_ = key;
    }

    // HKEY type is erased to prevent leaking Windows.h file, which has definitions that conflict
    // with raylib.h
    void *key_;
};

} // namespace jrat
