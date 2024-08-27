#include "ui.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include <string>

using namespace jrat;

CropUi::CropUi(const char *filepath, cv::Mat &&image)
    : Window("Resize Image", filepath), image_(image), filepath_(filepath) {
    ui_boxes();
}

void CropUi::update() {
    try {
        int top = std::stoi(std::string(text_boxes_[0].content_));
        int left = std::stoi(std::string(text_boxes_[1].content_));
        int bottom = std::stoi(std::string(text_boxes_[2].content_));
        int right = std::stoi(std::string(text_boxes_[3].content_));

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

void CropUi::ui_boxes() {
    create_text_box_left(4);
}

int CropUi::get_textbox(int index) {
    return std::stod(std::string(text_boxes_[index].content_));
}
