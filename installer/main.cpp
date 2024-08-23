#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "common/entrypoint.h"
#include "common/supported_types.h"
#include "registry_key.h"
#include "resources.h"
#include "ui.h"

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

void remove_dll_path() {
    std::string app_dir_str = APP_DIR.string();

    RegistryKey env_vars(
        RegistryKey::LOCAL_MACHINE,
        "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"
    );
    std::string path = env_vars.get_string("Path");

    size_t start = path.find(app_dir_str);
    if (start == std::string::npos) {
        return;
    }

    size_t end = start + app_dir_str.size();
    size_t len = app_dir_str.size();
    if (end < path.size() && path[end] == ';') {
        len++;
    }

    path.erase(start, len);
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

void delete_menu(const std::string &id, const std::vector<std::string> &sub_menu_ids) {
    RegistryKey command_store(
        RegistryKey::LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\CommandStore\\shell"
    );

    for (const std::string &sub_menu_id : sub_menu_ids) {
        command_store.delete_child(id + "." + sub_menu_id);
    }

    RegistryKey menu(RegistryKey::CLASSES_ROOT, "*\\shell");
    menu.delete_child(id);
}

std::string full_command(const std::string &app_name, const std::string args = "") {
    return (APP_DIR / app_name).string() + " " + args;
}

void install() {
    std::filesystem::create_directories(APP_DIR);

    add_dll_path();

    install_file("FLIPINATOR_EXE", "flipinator.exe");
    install_file("CONVERTINATOR_EXE", "convertinator.exe");
    install_file("CROPINATOR_EXE", "cropinator.exe");
    install_file("RESIZINATOR_EXE", "resizinator.exe");
    install_file("ROTATINATOR_EXE", "rotatinator.exe");
    install_file("OPENCV_DLL", "opencv_world490.dll");

    std::string supported_file_list = build_supported_file_list(supported_types);

    std::vector<MenuOption> operations = {
        {"Rotate 90 clockwise", "rotate90cw", full_command("rotatinator.exe", "%1 90 %1")},
        {"Rotate 90 counter-clockwise", "rotate90ccw", full_command("rotatinator.exe", "%1 -90 %1")
        },
    };
    add_menu("JRAT", "jrat", operations, supported_file_list);

    std::vector<MenuOption> conversions;
    for (const std::string &type : supported_types) {
        conversions.push_back(MenuOption{
            .display = "Convert to ." + type,
            .id = "convert." + type,
            .command = full_command("convertinator.exe", " %1 " + type),
        });
    }
    add_menu("JRAT: Convert", "jratconvert", conversions, supported_file_list);

    message_box("Installation complete!");
}

void uninstall() {
    std::filesystem::remove_all(APP_DIR);
    remove_dll_path();

    delete_menu("jrat", {"rotate90cw", "rotate90ccw"});

    std::vector<std::string> conversions;
    for (const std::string &type : supported_types) {
        conversions.push_back("convert." + type);
    }
    delete_menu("jratconvert", conversions);

    message_box("Uninstallation complete!");
}

} // namespace

int jrat::run(int argc, char **argv) {
    try {
        if (argc > 1 && std::string("--uninstall") == argv[1]) {
            uninstall();
        } else {
            install();
        }
        return 0;
    } catch (const std::exception &e) {
        std::string msg("A fatal installation error has occurred:\n");
        message_box(msg + e.what());
        return 1;
    }
}
