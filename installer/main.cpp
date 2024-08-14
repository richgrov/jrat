#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "common/supported_types.h"
#include "registry_key.h"
#include "resources.h"

using namespace jrat;

namespace {

static const std::filesystem::path APP_DIR = "C:\\Program Files\\JRAT";

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

void install_file(const char *id, const char *dest_name) {
    std::span<unsigned char> contents = get_resource(id);
    std::ofstream file(APP_DIR / dest_name, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error(std::format("couldn't open {}", dest_name));
    }

    file.write(reinterpret_cast<const char *>(&contents.front()), contents.size());
}

void add_dll_path() {
    std::string app_dir_str = APP_DIR.string();

    RegistryKey env_vars(
        RegistryKey::LOCAL_MACHINE,
        "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"
    );
    std::string path = env_vars.get_string("Path");

    bool already_set = path.find(app_dir_str) != std::string::npos;
    if (already_set) {
        return;
    }

    if (!path.ends_with(";")) {
        path.push_back(';');
    }
    path.append(app_dir_str);

    env_vars.set_string("Path", path);
}

} // namespace

int main(int argc, char **argv) {
    std::filesystem::create_directories(APP_DIR);

    add_dll_path();

    install_file("CONVERTINATOR_EXE", "convertinator.exe");
    install_file("OPENCV_DLL", "opencv_world490.dll");

    std::string supported_file_list = build_supported_file_list(supported_types);

    RegistryKey menu(RegistryKey::CLASSES_ROOT, "*\\shell\\jrat");
    menu.set_string("MUIVerb", "JRAT");
    menu.set_string("SubCommands", "jrat.resize");
    menu.set_string("AppliesTo", supported_file_list);

    RegistryKey command_store(
        RegistryKey::LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell"
    );

    RegistryKey resize_command(command_store, "jrat.resize");
    resize_command.set_string("MUIVerb", "Convert to .png");
    RegistryKey(resize_command, "command")
        .set_string("", (APP_DIR / "convertinator.exe %1 png").string());
    return 0;
}
