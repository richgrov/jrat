#define _USE_MATH_DEFINES

#define RAYGUI_IMPLEMENTATION

#include "common/window.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <raymath.h>
#include <stdexcept>

#include <raylib.h>
#include <raymath.h>

#include "JetBrainsMono.h"
#include "common/image_to_byte.h"

using namespace jrat;

Window::Window(const std::string &title, const char *image_path) {
    InitWindow(width_, height_, title.c_str());
    SetTargetFPS(60);
    image_path_ = const_cast<char *>(image_path);

    font_ =
        LoadFontFromMemory(".ttf", JetBrainsMono_ttf, sizeof(JetBrainsMono_ttf), 50, nullptr, 0);

    load_image(image_path);
    set_dimensions_and_position();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiSetFont(font_);
}

Window::~Window() {
    if (img_.height != 0) {
        UnloadTexture(img_);
    }
}

void Window::run() {
    while (!WindowShouldClose() && running_) {
        update_mouse();
        update();
        update_boxes();
        BeginDrawing();

        draw();
        draw_ui_bar();
        draw_boxes();
        EndDrawing();
    }
}

void jrat::Window::create_text_box(float x_pos, float y_pos, float width, float height) {
    text_boxes_.emplace_back(TextBox{x_pos, y_pos, width, height});
}

void jrat::Window::create_text_box_left() {
    float x_pos = 125 * text_box_count_ + 120;
    float y_pos = height_ - TEXT_BOX_VERTICAL_OFFSET;

    TextBox text_box = {x_pos, y_pos, TEXT_BOX_WIDTH, TEXT_BOX_HEIGHT, text_box_count_ != 0};

    text_boxes_.emplace_back(text_box);
    text_box_count_++;
}

void jrat::Window::create_text_box_left(int box_count) {
    for (int i = 0; i < box_count; i++) {
        create_text_box_left();
    }
}

void jrat::Window::create_text_box_left(const char *label) {
    float x_pos = 125 * text_box_count_ + 120;
    float y_pos = height_ - TEXT_BOX_VERTICAL_OFFSET;

    TextBox text_box = {x_pos, y_pos, TEXT_BOX_WIDTH, TEXT_BOX_HEIGHT, false};

    text_box_count_++;
    text_boxes_.emplace_back(text_box);
    labels_.push_back(label);
    label_positions_.push_back(x_pos);
    label_positions_.push_back(y_pos - 35);
}

void jrat::Window::load_image(const char *file_name) {
    if (img_.height != 0) {
        throw std::runtime_error("Can't load more than one image at a time.");
    }
    Image img = imageToBytes(file_name);
    img_ = LoadTextureFromImage(img);
}

void jrat::Window::set_dimensions_and_position() {
    int monitor = GetCurrentMonitor();
    width_ = GetMonitorWidth(monitor) / 2;
    height_ = GetMonitorHeight(monitor) / 2;

    SetWindowSize(width_, height_);
    SetWindowPosition(width_ - width_ / 2, height_ - height_ / 2);
}

void jrat::Window::close_window() {
    running_ = false;
}

void jrat::Window::draw_boxes() {

    ClearBackground(DARKGRAY);


    for (int i = 0; i < text_boxes_.size(); i++) {
        GuiTextBox(
            (text_boxes_[i].area()), text_boxes_[i].content_, text_boxes_[i].get_max_length(),
            active_text_box_ == i
        );
        if (text_boxes_[i].has_x()) {
            DrawTextEx(
                font_, "X", Vector2{text_boxes_[i].area().x - 18.5f, (float)(height_ - X_VERTICAL_OFFSET)}, X_FONT,
                1.0f, Color{0, 0, 0, 255}
            );
        }
    }
}

void jrat::Window::draw_image(Rectangle &source, Rectangle &destination, Vector2 &origin, double angle) {
    DrawTexturePro(img_, source, destination, origin, angle, Color{255, 255, 255, 255});
}

void jrat::Window::draw_ui_bar() {
    DrawRectangle(0, height_ - UI_BAR_HEIGHT, width_, UI_BAR_HEIGHT, Color{255, 255, 255, 255});
    for (int checkbox_count = 0; checkbox_count < check_box_checked_.size(); checkbox_count++) {
        bool check_bool = check_box_checked_[checkbox_count];

        int changed = GuiCheckBox(check_box_rects_[checkbox_count], "", &check_bool);
        if (changed == 1) {
            check_box_checked_[checkbox_count] = !check_box_checked_[checkbox_count];
        }
    }
    for (int label_count = 0; label_count < labels_.size(); label_count++) {
        DrawText(
            labels_[label_count], label_positions_[2 * label_count],
            label_positions_[2 * label_count + 1], 20, Color{255, 255, 255, 255}
        );
    }
    if ((GuiButton(
            Rectangle{
                (float)(width_ - 110), (float)(height_ - BUTTON_VERTICAL_OFFSET), BUTTON_WIDTH,
                BUTTON_HEIGHT
            },
            "Save"
        )
        )) { // returns true when clicked, wire up to save functionality

        save_image();
        CloseWindow();
    }

    if ((GuiButton(
            Rectangle{
                (float)(10), (float)(height_ - BUTTON_VERTICAL_OFFSET), BUTTON_WIDTH,
                BUTTON_HEIGHT
            },
            "Undo"
        )
        )) { // returns true when clicked, wire up to undo functionality

        undo_click();
    }
}

void jrat::Window::update_mouse() {
    mouse_pos_ = GetMousePosition();
}

void jrat::Window::add_checkbox_auto() {
    check_box_checked_.push_back(false);
    Rectangle rect = {
        (float)((TEXT_BOX_WIDTH + 25) * text_box_count_ + 10 +
                (CHECKBOX_WIDTH + 25) * (check_box_rects_.size() + 1)),
        (float)(height_ - CHECKBOX_VERTICAL_OFFSET),
        CHECKBOX_WIDTH, CHECKBOX_HEIGHT
    };
    check_box_rects_.push_back(rect);
}

void jrat::Window::add_checkbox(float x, float y) {
    check_box_checked_.push_back(false);
    Rectangle rect = {x, y, CHECKBOX_WIDTH, CHECKBOX_HEIGHT};
    check_box_rects_.push_back(rect);
}

void jrat::Window::update_boxes() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        bool box_found = false;
        for (int i = 0; i < text_boxes_.size(); i++) {

            if (CheckCollisionPointRec(mouse_pos_, text_boxes_[i].area())) {
                active_text_box_ = i;
                box_found = true;
                break;
            }
        }
        if (!box_found) {
            active_text_box_ = -1;
        }
    }

    if (IsKeyPressed(KEY_TAB)) {
        active_text_box_++;
        active_text_box_ %= text_boxes_.size();
    }
}
