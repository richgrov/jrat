#include "resize_ui.h"
#include <filesystem>
#include <iostream>

using namespace jrat;

void jrat::Resize_Ui::load_font() {
    //font_ = LoadFont("C:/PRO-100/jrat/common/resources/JetBrainsMono.ttf");
}

void jrat::Resize_Ui::update() {}

void jrat::Resize_Ui::draw() {
    DrawTextEx(font_, "X", Vector2{123, 572}, 16.0f, 1.0f, BLACK);
}
