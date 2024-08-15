#include <filesystem>
#include <fstream>
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

struct MenuOption {
    std::string display;
    std::string id;
    std::string command;
};

void add_menu(
    const std::string &display, const std::string &id, const std::vector<MenuOption> &options,
    const std::string &file_pattern
) {
    RegistryKey command_store(
        RegistryKey::LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell"
    );

    std::string option_list;
    for (const MenuOption &option : options) {
        std::string full_id = id + "." + option.id;

        RegistryKey command(command_store, full_id);
        command.set_string("MUIVerb", option.display);
        RegistryKey(command, "command").set_string("", option.command);

        option_list += full_id + ";";
    }

    RegistryKey menu(RegistryKey::CLASSES_ROOT, "*\\shell\\" + id);
    menu.set_string("MUIVerb", display);
    menu.set_string("SubCommands", option_list);
    menu.set_string("AppliesTo", file_pattern);
}

std::string full_command(const std::string &app_name, const std::string args = "") {
    return (APP_DIR / app_name).string() + args;
}

} // namespace

int main(int argc, char **argv) {
    std::filesystem::create_directories(APP_DIR);

    add_dll_path();

    install_file("FLIPINATOR_EXE", "flipinator.exe");
    install_file("CONVERTINATOR_EXE", "convertinator.exe");
    install_file("CROPINATOR_EXE", "cropinator.exe");
    install_file("RESIZINATOR_EXE", "resizinator.exe");
    install_file("ROTATINATOR_EXE", "rotatinator.exe");
    install_file("OPENCV_DLL", "opencv_world490.dll");

    std::string supported_file_list = build_supported_file_list(supported_types);

    std::vector<MenuOption> conversions;
    for (const std::string &type : supported_types) {
        conversions.push_back(MenuOption{
            .display = "Convert to ." + type,
            .id = "jrat.convert." + type,
            .command = (APP_DIR / "convertinator.exe").string() + " %1 " + type,
        });
    }
    add_menu("JRAT: Convert", "jratconvert", conversions, supported_file_list);

    return 0;
}
