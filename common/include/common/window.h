#pragma once

#include <string>
#include <vector>

#include <raylib.h>

#include "textbox.h"

namespace jrat {

class Window {
public:
    explicit Window(int width, int height, const std::string &title);

    ~Window();

    void run();

    void create_text_box(float x_pos, float y_pos, float width, float height);
    void create_text_box_left(int box_num);

protected:
    void load_image(const char *file_name);
    void set_width_and_height();
    virtual void load_font();
    virtual void ui_boxes() = 0;
    virtual void update() = 0;
    void update_boxes();
    virtual void draw() = 0;
    void draw_boxes();
    void draw_image();
    void draw_ui_bar();
    int width_{0};
    int height_{0};
    int text_box_count_{0};
    Font font_{};
    Texture2D img_{};

    std::vector<TextBox> text_boxes_;

    Vector2 mouse_pos_{0, 0};

    int active_text_box_{-1};
    bool check_box_checked_{true};
};

} // namespace jrat
