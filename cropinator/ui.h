#pragma once

#include "common/window.h"

namespace jrat {

class CropUi : public Window {
public:
    CropUi(const char *filepath);

    virtual void ui_boxes() override;
    virtual void update() override {}
    virtual void save_image() override {}

    virtual void draw() override {}
};

} // namespace jrat
