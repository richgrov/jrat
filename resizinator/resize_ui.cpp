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

void ResizeUi::draw() {
    float scale = resize_height_ > resize_width_
                      ? (static_cast<float>(height_) - UI_BAR_HEIGHT) / resize_height_
                      : static_cast<float>(width_) / resize_width_;
    scale *= IMAGE_SCREEN_COVERAGE;

    float scaled_width = static_cast<float>(resize_width_) * scale;
    float scaled_height = static_cast<float>(resize_height_) * scale;

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
        .width = scaled_width,
        .height = scaled_height,
    };

    draw_image(source, destination, origin, 0);
}

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
    create_text_box_left("Width");
    create_text_box_left("Height");
}

void ResizeUi::read_boxes() {
    try {
        resize_width_ = get_textbox_float(text_boxes_[0].content_);
        resize_height_ = get_textbox_float(text_boxes_[1].content_);

        cv::Size size{resize_width_, resize_height_};
        if (undo_.top() == size) {
            return;
        }
        undo_.push(size);
        // todo: read checkbox for keep aspect ratio
    } catch (const std::exception &) {
    }
}

void ResizeUi::set_boxes() {
    text_boxes_[0].set_content(std::to_string(resize_width_));
    text_boxes_[1].set_content(std::to_string(resize_height_));
}
