#pragma once

#include "textbox.h"

#include <raylib.h>
#include <string>
#include <vector>

namespace jrat {

class Window {
public:
    explicit Window(int width, int height, const std::string &title);

    ~Window();

    void run();

    void create_text_box(float x_pos, float y_pos, float width, float height);

protected:
    virtual void load_font() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void draw_boxes();
    virtual void update_boxes();
    int width_{0};
    int height_{0};
    Font font_{NULL};

    
    std::vector<TextBox> text_boxes_;

    Vector2 mouse_pos_{0, 0};

    int active_text_box_{-1};
};

} // namespace jrat
