#pragma once

#include "raylib.h"
#include <common/window.h>

namespace jrat {

class WindowExample : public Window {
public:
    WindowExample() : Window(640, 480, "Example") {}

protected:
    virtual void update() override {};
    virtual void draw() override {
        DrawText("hello", 50, 50, 50, WHITE);
    }
};

} // namespace jrat
