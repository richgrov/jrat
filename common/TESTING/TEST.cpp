#include "TEST.h"

namespace jrat {

TestUI::TestUI(const std::string &title, const char *file_name) : Window(title, file_name) {
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
