#include "ui.h"

#include <Windows.h>

using namespace jrat;

void jrat::report_fatal_error(const std::string &msg) {
    std::string full_msg = "A fatal installation error has occurred:\n" + msg;
    MessageBox(nullptr, full_msg.c_str(), "Installer cannot continue", MB_OK);
}
