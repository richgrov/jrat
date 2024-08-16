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
};
} // namespace jrat
