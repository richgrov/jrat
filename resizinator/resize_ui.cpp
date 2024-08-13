#include "resize_ui.h"

using namespace jrat;

void jrat::ResizeUi::load_font() {
    //font_ = LoadFont("C:/PRO-100/jrat/common/resources/JetBrainsMono.ttf");
}

void jrat::ResizeUi::update() {}

void jrat::ResizeUi::draw() {
    DrawTextEx(font_, "X", Vector2{123, 572}, 16.0f, 1.0f, BLACK);
}
