#include "rotate_ui.h"
#include "rotatinator.h"

#include <format>
#include <iostream>

using namespace jrat;

RotateUi::RotateUi(const std::string &title, const char *file_name, cv::Mat &image)
    : Window(title, file_name) {
    angle_ = 0;

    ui_boxes();
    set_boxes();

    open_image_ = image;
    save_file_ = file_name;
}

void RotateUi::update() {
    read_boxes();
}

void RotateUi::draw() {}

void RotateUi::save_image() {
    read_boxes();
    write_image(open_image_, angle_, save_file_);
}

void RotateUi::ui_boxes() {
    create_text_box_left(1);
}

void RotateUi::read_boxes() {
    try {
        angle_ = std::stold(std::string(text_boxes_[0].content_));
    } catch (const std::exception &) {
    }
}

void RotateUi::set_boxes() {
    text_boxes_[0].set_content(std::format("{}", angle_));
}
