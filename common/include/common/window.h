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
    virtual void update_image() = 0;
    virtual void update_mouse();
    void add_checkbox_auto();
    void add_checkbox(float x, float y);
    void close_window();
    void create_text_box(float x_pos, float y_pos, float width, float height);
    void create_text_box_left();
    void create_text_box_left(int box_count);
    void create_text_box_left(const char *label);
    void draw_image(Rectangle &destination, Vector2 &origin, double angle);
    void draw_boxes();
    void draw_ui_bar();
    void update_boxes();

    void set_image_mask(float x, float y, float width, float height) {
        img_mask_.x = x;
        img_mask_.y = y;
        img_mask_.width = width;
        img_mask_.height = height;
    }

    char *image_path_{};
    // Temporary values needed to properly initialize raylib
    int width_{500};
    int height_{500};
    int text_box_count_{0};
    Font font_{};
    Texture2D img_{};

    std::vector<const char *> labels_;
    std::vector<int> label_positions_;
    std::vector<TextBox> text_boxes_;
    std::vector<Rectangle> check_box_rects_;

    Vector2 mouse_pos_{0, 0};

    int active_text_box_{-1};
    std::vector<bool> check_box_checked_;
    bool running_{true};

    Rectangle img_mask_{};

private:
    void load_image(const char *file_name);
    void set_dimensions_and_position();
};

} // namespace jrat
