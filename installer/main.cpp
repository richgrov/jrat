#include <filesystem>

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

static const std::filesystem::path APP_DIR = "C:\\Program Files\\JRAT";

int main(int argc, char **argv) {
    std::filesystem::create_directories(APP_DIR);

    std::string supported_file_list = build_supported_file_list(supported_files);

    RegistryKey menu(RegistryKey::CLASSES_ROOT, "*\\shell\\jrat");
    menu.set_string("MUIVerb", "JRAT");
    menu.set_string("SubCommands", "jrat.resize");
    menu.set_string("AppliesTo", supported_file_list);

    RegistryKey command_store(
        RegistryKey::LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell"
    );

    RegistryKey resize_command(command_store, "jrat.resize");
    resize_command.set_string("MUIVerb", "Resize...");
    RegistryKey(resize_command, "command").set_string("", "notepad.exe %1");
    return 0;
}
