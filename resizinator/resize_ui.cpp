#include "resize_ui.h"
#include "resizinator.h"

using namespace jrat;

ResizeUi::ResizeUi(
    int width, int height, const std::string &title, const char *file_name, cv::Mat image
)
    : Window(width, height, title, file_name) {
    load_font();
    load_image(file_name);
    set_dimensions_and_position();
    ui_boxes();

    open_image_ = image;
    save_file_ = file_name;
}

void ResizeUi::update() {}

void ResizeUi::draw() {}

void ResizeUi::save_image() {
    write_image(open_image_, resize_width_, resize_height_, keep_aspect_ratio_, save_file_);
}

void ResizeUi::ui_boxes() {
    create_text_box_left(3);
}
