#pragma once
#include "common/window.h"

#include <opencv2/core/mat.hpp>

#include <stack>
#include <string>
namespace jrat {

class ResizeUi : public Window {
public:
    ResizeUi() = default;
    ResizeUi(const std::string &title, const char *file_name, cv::Mat image);

    virtual void update() override;
    virtual void draw() override;
    virtual void save_image() override;
    virtual void undo_click() override;
    virtual void ui_boxes() override;
    virtual void update_image() override;
    void read_boxes();
    void set_boxes();

private:
    int resize_width_;
    int resize_height_;
    bool keep_aspect_ratio_;
    cv::Mat open_image_;
    std::string save_file_;
    std::stack<cv::Size> undo_;
};
} // namespace jrat
