#include "resize_ui.h"

using namespace jrat;

jrat::ResizeUi::ResizeUi(int width, int height, const std::string &title)
    : Window(width, height, title) {
    font_ = LoadFontFromMemory(".ttf", JetBrainsMono_ttf, sizeof(JetBrainsMono_ttf), 50, 0, 255);
    create_text_box(10, 570, 100, 20);
    create_text_box(135, 570, 100, 20);
}

void jrat::ResizeUi::load_font() {}

void jrat::ResizeUi::update() {}

void jrat::ResizeUi::draw() {
    DrawTextEx(font_, "X", Vector2{123, 572}, 16.0f, 1.0f, BLACK);
}
