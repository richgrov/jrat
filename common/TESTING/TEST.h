#pragma once
#include "common/window.h"

namespace jrat {

class TestUI : public Window {
public:
    TestUI(const std::string &title, const char *file_name);

protected:
    virtual void ui_boxes() override;
    virtual void update() override;
    virtual void save_image() override;
    virtual void undo_click() override;
    virtual void draw() override;
};

} // namespace jrat
