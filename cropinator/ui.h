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
    virtual void draw() override;
    virtual void undo_click() override;
    void set_boxes();

private:
    int get_textbox(int index);

    cv::Mat image_;
    std::string filepath_;
    std::stack<Vector4> undo_;
    Rectangle img_mask_{};

    void set_image_mask(float x, float y, float width, float height) {
        img_mask_.x = x;
        img_mask_.y = y;
        img_mask_.width = width;
        img_mask_.height = height;
    }
};

} // namespace jrat
