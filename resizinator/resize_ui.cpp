#include "resize_ui.h"

using namespace jrat;

jrat::ResizeUi::ResizeUi(int width, int height, const std::string &title, const char *file_name)
    : Window(width, height, title) {
    load_font();
    load_image(file_name);
    set_dimensions_and_position();
    ui_boxes();
}

void jrat::ResizeUi::update() {}

void jrat::ResizeUi::draw() {}

void jrat::ResizeUi::ui_boxes() {
    create_text_box_left(3);
}
