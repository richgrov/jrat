#include "ui.h"

#include <Windows.h>

using namespace jrat;

void jrat::report_fatal_error(const std::string &msg) {
    MessageBox(nullptr, msg.c_str(), "Installer cannot continue", MB_OK);
}
