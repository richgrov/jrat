#include "resize_ui.h"
#include "resizinator.h"

#include <opencv2/opencv.hpp>

using namespace jrat;

ResizeUi::ResizeUi(const std::string &title, const char *file_name, cv::Mat image)
    : Window(title, file_name) {
    cv::Size size = image.size();

    resize_width_ = size.width;
    resize_height_ = size.height;
    keep_aspect_ratio_ = false;

    ui_boxes();
    set_boxes();

    open_image_ = image;
    save_file_ = file_name;
}

void ResizeUi::update() {
    read_boxes();
}

void ResizeUi::draw() {}

void ResizeUi::update_image() {
    //float hypot = sqrtf(static_cast<float>(resize_width_ * resize_width_ + resize_height_ * resize_height_));
    // Amount to scale the image by to ensure it stays within bounds of the window + some padding
    float scale = resize_height_ > resize_width_ ? (height_ - 50.0f) / resize_height_ : static_cast<float>(width_) / resize_width_;
    scale *= 0.9f;

    float scaled_width = static_cast<float>(resize_width_) * scale;
    float scaled_height = static_cast<float>(resize_height_) * scale;

    Vector2 origin = {scaled_width / 2, scaled_height / 2};

    float left = (static_cast<float>(width_) - scaled_width) / 2.f;
    float top = (static_cast<float>(height_ - 50) - scaled_height) / 2.f;

    Rectangle destination = {
        .x = (left + origin.x + img_mask_.x * scale),
        .y = (top + origin.y + img_mask_.y * scale),
        .width = scaled_width,
        .height = scaled_height,
    };

    draw_image(destination, origin, 0);
}

void ResizeUi::save_image() {
    read_boxes();
    write_image(open_image_, resize_width_, resize_height_, keep_aspect_ratio_, save_file_);
}

void ResizeUi::ui_boxes() {
    create_text_box_left(2);
}

void ResizeUi::read_boxes() {
    try {
        resize_width_ = std::stoi(std::string(text_boxes_[0].content_));
        resize_height_ = std::stoi(std::string(text_boxes_[1].content_));
        // todo: read checkbox for keep aspect ratio
    } catch (const std::exception &) {}
}

void ResizeUi::set_boxes() {
    text_boxes_[0].set_content(std::to_string(resize_width_));
    text_boxes_[1].set_content(std::to_string(resize_height_));
}
