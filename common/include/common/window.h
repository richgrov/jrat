#pragma once

#include <string>
#include <vector>

#include <raylib.h>

#include "textbox.h"

namespace jrat {

typedef unsigned char byte;

class Window {
public:
    explicit Window(int width, int height, const std::string &title, const char *file_path);

    ~Window();

    void run();

    void create_text_box(float x_pos, float y_pos, float width, float height);
    void create_text_box_left(int box_count);

protected:
    void load_image(const char *file_name);
    void set_dimensions_and_position();
    virtual void load_font();
    virtual void ui_boxes() = 0;
    virtual void update() = 0;
    virtual void save_image() = 0;
    virtual void update_mouse();
    void update_boxes();
    virtual void draw() = 0;
    void draw_boxes();
    void draw_image();
    void draw_ui_bar();
    char *image_path_{};
    int width_{0};
    int height_{0};
    int text_box_count_{0};
    Font font_{};
    Texture2D img_{};

    std::vector<TextBox> text_boxes_;

    Vector2 mouse_pos_{0, 0};

    int active_text_box_{-1};
    bool check_box_checked_{true};

    // image manipulation
    double angle_{0};
};

} // namespace jrat
