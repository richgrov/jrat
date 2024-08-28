#include "rotate_ui.h"
#include "rotatinator.h"

#include <format>
#include <iostream>

using namespace jrat;

RotateUi::RotateUi(const std::string &title, const char *file_name, cv::Mat &image)
    : Window(title, file_name) {
    ui_boxes();
    set_boxes();

    undo_.push(0);
    open_image_ = image;
    save_file_ = file_name;
}

void RotateUi::update() {
    read_boxes();
}

void RotateUi::draw() {
    float hypot = sqrtf(static_cast<float>(img_.width * img_.width + img_.height * img_.height));
    // Amount to scale the image by to ensure it stays within bounds of the window + some padding
    float scale = width_ > height_ ? (height_ - UI_BAR_HEIGHT) / hypot : width_ / hypot;
    scale *= IMAGE_SCREEN_COVERAGE;

    float scaled_width = static_cast<float>(img_.width) * scale;
    float scaled_height = static_cast<float>(img_.height) * scale;

    Vector2 origin = {scaled_width / 2, scaled_height / 2};

    float left = (static_cast<float>(width_) - scaled_width) / 2.f;
    float top = (static_cast<float>(height_ - UI_BAR_HEIGHT) - scaled_height) / 2.f;

    Rectangle source = {
        .x = 0.f,
        .y = 0.f,
        .width = static_cast<float>(img_.width),
        .height = static_cast<float>(img_.height),
    };

    Rectangle destination = {
        .x = left + origin.x,
        .y = top + origin.y,
        .width = img_.width * scale,
        .height = img_.height * scale,
    };

    draw_image(source, destination, origin, angle_);
}

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
