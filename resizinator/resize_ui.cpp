#include "resize_ui.h"
#include "JetBrainsMono.h"


using namespace jrat;

jrat::ResizeUi::ResizeUi(int width, int height, const std::string &title)
    : Window(width, height, title) {
    font_ =
        LoadFontFromMemory(".ttf", JetBrainsMono_ttf, sizeof(JetBrainsMono_ttf), 50, nullptr, 0);
}

void jrat::ResizeUi::load_font() {}

void jrat::ResizeUi::update() {}

void jrat::ResizeUi::draw() {
    DrawTextEx(font_, "X", Vector2{123, 572}, 16.0f, 1.0f, BLACK);
}
