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

    undo_.push(cv::Size(resize_width_, resize_height_));
    open_image_ = image;
    save_file_ = file_name;
}

void ResizeUi::update() {
    read_boxes();
}

void ResizeUi::draw() {}

void ResizeUi::save_image() {
    read_boxes();
    write_image(open_image_, resize_width_, resize_height_, keep_aspect_ratio_, save_file_);
}

void jrat::ResizeUi::undo_click() {
    if (undo_.size() == 1) {
        return;
    }
    undo_.pop();
    resize_width_ = undo_.top().width;
    resize_height_ = undo_.top().height;
    text_boxes_[0].set_content(std::to_string(resize_width_));
    text_boxes_[1].set_content(std::to_string(resize_height_));
}

void ResizeUi::ui_boxes() {
    create_text_box_left(2);
}

void ResizeUi::read_boxes() {
    try {
        resize_width_ = std::stoi(std::string(text_boxes_[0].content_));
        resize_height_ = std::stoi(std::string(text_boxes_[1].content_));
        if (undo_.top().width == resize_width_ && undo_.top().height == resize_height_) {
            return;
        }
        undo_.push(cv::Size(resize_width_, resize_height_));
        // todo: read checkbox for keep aspect ratio
    } catch (const std::exception &) {
        std::cerr << "textbox couldn't be converted to int";
    }
}

void ResizeUi::set_boxes() {
    text_boxes_[0].set_content(std::to_string(resize_width_));
    text_boxes_[1].set_content(std::to_string(resize_height_));
}
