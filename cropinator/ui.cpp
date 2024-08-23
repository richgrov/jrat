#include "ui.h"

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include <string>

using namespace jrat;

CropUi::CropUi(const char *filepath, cv::Mat &&image)
    : Window(1280, 720, "Resize Image", filepath), image_(image), filepath_(filepath) {
    load_font();
    load_image(filepath);
    set_dimensions_and_position();
    ui_boxes();
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
