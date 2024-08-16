#pragma once
#include "common/window.h"

#include <string>
namespace jrat {

class ResizeUi : public Window {
public:
    ResizeUi() = default;
    ResizeUi(int width, int height, const std::string &title, const char *file_name);

    virtual void update() override;
    virtual void draw() override;
    virtual void save_image() override;
    virtual void ui_boxes() override;

private:
    int resize_width_;
    int resize_height_;
    bool keep_aspect_ratio_;
    std::string open_file_;
    std::string save_file_;
};
} // namespace jrat
