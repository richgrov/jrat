#pragma once

#include <string>
#include <vector>

#include <raylib.h>

#include "textbox.h"

namespace jrat {

typedef unsigned char byte;

class Window {
public:
    explicit Window(const std::string &title, const char *file_path);

    ~Window();

    void run();

protected:
    virtual void draw() = 0;
    virtual void save_image() = 0;
    virtual void ui_boxes() = 0;
    virtual void update() = 0;
    virtual void update_mouse();
    void add_checkbox_auto();
    void add_checkbox(float x, float y);
    void close_window();
    void create_text_box(float x_pos, float y_pos, float width, float height);
    void create_text_box_left(int box_count);
    void draw_boxes();
    void draw_image();
    void draw_ui_bar();
    void update_boxes();

    void set_image_mask(float x, float y, float width, float height) {
        img_mask_.x = x;
        img_mask_.y = y;
        img_mask_.width = width;
        img_mask_.height = height;
    }

    char *image_path_{};
    int width_{0};
    int height_{0};
    int text_box_count_{0};
    Font font_{};
    Texture2D img_{};

    std::vector<TextBox> text_boxes_;
    std::vector<Rectangle> check_box_rects_;

    Vector2 mouse_pos_{0, 0};

    int active_text_box_{-1};
    std::vector<bool> check_box_checked_;
    bool running_{true};

    // image manipulation
    double angle_{0};

private:
    void load_image(const char *file_name);
    void set_dimensions_and_position();

    Rectangle img_mask_{};
};

} // namespace jrat
