#include "TEST.h"

namespace jrat {

TestUI::TestUI(int width, int height, const std::string &title, const char *file_name)
    : Window(width, height, title, file_name) {
    load_font();
    load_image(file_name);
    set_dimensions_and_position();
    ui_boxes();
    add_checkbox_auto();
    add_checkbox_auto();
    add_checkbox_auto();
    add_checkbox_auto();
    add_checkbox_auto();
    add_checkbox_auto();
    add_checkbox(0, 0);
}

void TestUI::ui_boxes() {
    create_text_box_left(2);
}

void TestUI::update() {}

void TestUI::save_image() {
    close_window();
}

void TestUI::draw() {}

} // namespace jrat