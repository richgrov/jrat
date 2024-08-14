#include "resize_ui.h"

using namespace jrat;

jrat::ResizeUi::ResizeUi(int width, int height, const std::string &title, const char *file_name)
    : Window(width, height, title) {
    load_font();
    load_image(file_name);
    set_width_and_height();
    ui_boxes();
}

void jrat::ResizeUi::update() {}

void jrat::ResizeUi::draw() {
    DrawTextEx(font_, "X", Vector2{1, 1}, 40.0f, 1.0f, BLACK);
}

void jrat::ResizeUi::ui_boxes() {
    create_text_box_left();
    create_text_box_left();
    create_text_box_left();
}
