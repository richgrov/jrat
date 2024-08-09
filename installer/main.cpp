#include "registry_key.h"

using namespace jrat;

int main(int argc, char **argv) {
    RegistryKey menu(RegistryKey::CLASSES_ROOT, "*\\shell\\jrat");
    menu.set_string("MUIVerb", "JRAT");
    menu.set_string("SubCommands", "Windows.delete");
    menu.set_string("AppliesTo", ".jpeg OR .jpg OR .png OR .tiff");
    return 0;
}
