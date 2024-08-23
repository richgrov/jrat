#include "ui.h"

#include <Windows.h>

using namespace jrat;

void jrat::message_box(const std::string &msg) {
    MessageBox(nullptr, msg.c_str(), "JRAT", MB_OK);
}
