#include "TEST.h"


namespace jrat {

TestUI::TestUI(int width, int height, const std::string &title, const char *file_name) 
    : Window(width, height, title) {
    load_font();
    load_image(file_name);
    set_dimensions_and_position();
    ui_boxes();
}

void TestUI::ui_boxes() {}

void TestUI::update() {}

void TestUI::save_image() {}

void TestUI::draw() {}

}