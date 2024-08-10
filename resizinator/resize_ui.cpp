#include "resize_ui.h"
#include <filesystem>
#include <iostream>

using namespace jrat;

void jrat::Resize_Ui::load_font() {
    font_ = LoadFont("C:/PRO-100/jrat/common/resources/JetBrainsMono.ttf");
}
