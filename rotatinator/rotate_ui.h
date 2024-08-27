#pragma once
#include "common/window.h"

#include <opencv2/core/mat.hpp>

#include <stack>
#include <string>

namespace jrat {

class RotateUi : public Window {
public:
    RotateUi() = default;
    RotateUi(const std::string &title, const char *file_name, cv::Mat &image);

    virtual void update() override;
    virtual void draw() override;
    virtual void save_image() override;
    virtual void undo_click() override;
    virtual void ui_boxes() override;
    void read_boxes();
    void set_boxes();

private:
    cv::Mat open_image_;
    std::string save_file_;
    std::stack<double> undo_;
};
} // namespace jrat
