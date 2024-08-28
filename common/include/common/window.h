#pragma once

#include <string>
#include <vector>

#include <raylib.h>

#include "textbox.h"

namespace jrat {

constexpr float IMAGE_SCREEN_COVERAGE = 0.9f;
constexpr int UI_BAR_HEIGHT = 85;
constexpr int TEXT_BOX_HEIGHT = 40;
constexpr int TEXT_BOX_WIDTH = 100;
constexpr int BUTTON_HEIGHT = 30;
constexpr int BUTTON_WIDTH = 100;
constexpr int CHECKBOX_HEIGHT = 30;
constexpr int CHECKBOX_WIDTH = CHECKBOX_HEIGHT;
constexpr float X_FONT = 24;
constexpr int X_VERTICAL_OFFSET = X_FONT + (UI_BAR_HEIGHT - X_FONT) / 2;
constexpr int CHECKBOX_VERTICAL_OFFSET = CHECKBOX_HEIGHT + (UI_BAR_HEIGHT - CHECKBOX_HEIGHT) / 2;
constexpr int TEXT_BOX_VERTICAL_OFFSET = TEXT_BOX_HEIGHT + (UI_BAR_HEIGHT - TEXT_BOX_HEIGHT) / 2;
constexpr int BUTTON_VERTICAL_OFFSET = BUTTON_HEIGHT + (UI_BAR_HEIGHT - BUTTON_HEIGHT) / 2;

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
    virtual void undo_click() = 0;
    virtual void update_mouse();
    void add_checkbox_auto();
    void add_checkbox(float x, float y);
    void close_window();
    void create_text_box(float x_pos, float y_pos, float width, float height);
    void create_text_box_left();
    void create_text_box_left(int box_count);
    void create_text_box_left(const char *label);
    void draw_image(Rectangle &mask, Rectangle &destination, Vector2 &origin, double angle);
    void draw_boxes();
    void draw_ui_bar();
    void update_boxes();

    float get_textbox_float(char *content) {
        bool empty = content[0] == '\0';
        return empty ? 0 : std::atoi(content);
    };

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

private:
    void load_image(const char *file_name);
    void set_dimensions_and_position();
};

} // namespace jrat
