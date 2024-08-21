#pragma once
#include "common/window.h"

namespace jrat {

class TestUI : public Window {
public:
    TestUI(int width, int height, const std::string &title, const char *file_name);

protected:

    virtual void ui_boxes();
    virtual void update();
    virtual void save_image();
    virtual void draw();


};

} // namespace jrat