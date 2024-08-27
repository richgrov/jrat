#pragma once

#include <opencv2/core/mat.hpp>
#include <stack>

#include "common/window.h"


namespace jrat {

class CropUi : public Window {
public:
    CropUi(const char *filepath, cv::Mat &&image);

    virtual void ui_boxes() override;
    virtual void update() override;
    virtual void save_image() override;
    virtual void update_image() override;
    virtual void undo_click() override;
    void set_boxes();

    virtual void draw() override {}

private:
    int get_textbox(int index);

    cv::Mat image_;
    std::string filepath_;
    std::stack<Vector4> undo_;
};

} // namespace jrat
