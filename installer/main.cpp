#include "common/supported_files.h"
#include "registry_key.h"

using namespace jrat;

std::string build_supported_file_list(const std::vector<std::string> &files) {
    std::string result;
    for (int i = 0; i < files.size(); ++i) {
        if (i != 0) {
            result.append(" OR ");
        }
        result.push_back('.');
        result.append(files[i]);
    }
    return result;
}

int main(int argc, char **argv) {
    std::string supported_file_list = build_supported_file_list(supported_files);
    RegistryKey menu(RegistryKey::CLASSES_ROOT, "*\\shell\\jrat");
    menu.set_string("MUIVerb", "JRAT");
    menu.set_string("SubCommands", "Windows.delete");
    menu.set_string("AppliesTo", supported_file_list);
    return 0;
}
