#include "rotate_ui.h"
#include "rotatinator.h"
#include "common/window.h"

using namespace jrat;

RotateUi::RotateUi(int width, int height, const std::string &title, const char *file_name, cv::Mat &image)
    : Window(width, height, title, file_name) {
    load_font();
    load_image(file_name);
    set_dimensions_and_position();
    ui_boxes();

    open_image_ = image;
    save_file_ = file_name;
}

void RotateUi::update() {}

void RotateUi::draw() {}

void RotateUi::save_image() {
    write_image(open_image_, angle_, save_file_);
}

void RotateUi::ui_boxes() {
    create_text_box_left(1);
}
