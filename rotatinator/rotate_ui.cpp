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

    undo_.push(0);
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

void jrat::RotateUi::undo_click() {
    if (undo_.size() == 1) {
        return;
    }
    undo_.pop();
    angle_ = undo_.top();
    std::string angle = std::to_string((int)angle_);
    text_boxes_[0].set_content(angle);
}

void RotateUi::ui_boxes() {
    create_text_box_left(1);
}

void RotateUi::read_boxes() {
    try {
        angle_ = std::stold(std::string(text_boxes_[0].content_));
        if (undo_.top() == angle_) {
            return;
        }
        undo_.push(angle_);
    } catch (const std::exception &ex) {
    }
}

void RotateUi::set_boxes() {
    text_boxes_[0].set_content(std::format("{}", angle_));
}
