#include "ui.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include <string>
#include <format>

using namespace jrat;

CropUi::CropUi(const char *filepath, cv::Mat &&image)
    : Window("Resize Image", filepath), image_(image), filepath_(filepath) {
    ui_boxes();

    set_boxes();

    undo_.push(Vector4{ 0,0,0,0 });
}

void CropUi::update() {
    try {
        float top = std::stoi(std::string(text_boxes_[0].content_));
        float left = std::stoi(std::string(text_boxes_[1].content_));
        float bottom = std::stoi(std::string(text_boxes_[2].content_));
        float right = std::stoi(std::string(text_boxes_[3].content_));
        if (undo_.top().x == top && undo_.top().y == left && undo_.top().z == bottom &&
            undo_.top().w == right) {
            return;
        }

        undo_.push(Vector4{top, left, bottom, right});
        Vector4 something{1, 2, 4, 5};

        set_image_mask(
            static_cast<float>(left), static_cast<float>(top), img_.width - left - right,
            img_.height - top - bottom
        );
    } catch (const std::exception &) {
    }
}

void CropUi::save_image() {
    int top = get_textbox(0);
    int left = get_textbox(1);
    int bottom = get_textbox(2);
    int right = get_textbox(3);

    cv::Mat cropped =
        image_(cv::Range(top, image_.rows - bottom), cv::Range(left, image_.cols - right));
    cv::imwrite(filepath_, cropped);
}

void jrat::CropUi::undo_click() {
    if (undo_.size() == 1) {
        return; 
    }
    undo_.pop();
    text_boxes_[0].set_content(std::to_string((int)undo_.top().x));
    text_boxes_[1].set_content(std::to_string((int)undo_.top().y));
    text_boxes_[2].set_content(std::to_string((int)undo_.top().z));
    text_boxes_[3].set_content(std::to_string((int)undo_.top().w));

    set_image_mask(static_cast<float>(undo_.top().y), static_cast<float>(undo_.top().x),
                   img_.width - undo_.top().y - undo_.top().w,
                   img_.height - undo_.top().x - undo_.top().z 
    );
}

void CropUi::ui_boxes() {
    create_text_box_left(4);
}

int CropUi::get_textbox(int index) {
    return std::stod(std::string(text_boxes_[index].content_));
}

void CropUi::set_boxes() {
    text_boxes_[0].set_content(std::format("{}", 0));
    text_boxes_[1].set_content(std::format("{}", 0));
    text_boxes_[2].set_content(std::format("{}", 0));
    text_boxes_[3].set_content(std::format("{}", 0));
}
