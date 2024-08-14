#include "common/window.h"
#include "JetBrainsMono.h"

#include <iostream>
#include <raylib.h>
#include <stdexcept>

using namespace jrat;

Window::Window(int width, int height, const std::string &title) {
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
}

Window::~Window() {
    if (img_.height != 0) {
        UnloadTexture(img_);
    }
    CloseWindow();
}

void Window::run() {
    while (!WindowShouldClose()) {
        update();
        update_boxes();
        BeginDrawing();

        draw();
        draw_image();
        draw_ui_bar();
        draw_boxes();
        EndDrawing();
    }
}

void jrat::Window::create_text_box(float x_pos, float y_pos, float width, float height) {
    text_boxes_.emplace_back(TextBox{x_pos, y_pos, width, height});
}

void jrat::Window::create_text_box_left(int box_num) {
    for (int i = 0; i < box_num; i++) {
        text_boxes_.emplace_back(
            TextBox{(float)(125 * text_box_count_ + 10), (float)(height_ - 35), 100, 20}
        );
        text_box_count_++;
    }
}

void jrat::Window::load_image(const char *file_name) {
    if (img_.height != 0) {
        throw std::runtime_error("Can't load more than one image at a time.");
    } else {
        img_ = LoadTexture(file_name);
    }
}

void jrat::Window::set_width_and_height() {
    if (img_.height != 0) {
        width_ = img_.width + 100;
        height_ = img_.height + 100;
    }
    SetWindowSize(width_, height_);
}

void jrat::Window::load_font() {
    font_ =
        LoadFontFromMemory(".ttf", JetBrainsMono_ttf, sizeof(JetBrainsMono_ttf), 50, nullptr, 0);
}

void jrat::Window::draw_boxes() {

    ClearBackground(WHITE);

    for (int i = 0; i < text_boxes_.size(); i++) {
        GuiTextBox(
            text_boxes_[i].area(), text_boxes_[i].content_, text_boxes_[i].get_max_length(),
            active_text_box_ == i
        );
    }
}

void jrat::Window::draw_image() {

    DrawTextureEx(img_, Vector2{50, 50}, 0, 1, Color{255, 255, 255, 255});
}

void jrat::Window::draw_ui_bar() {
    GuiCheckBox(
        Rectangle{(float)(125 * text_box_count_ + 10), (float)(height_ - 40), 30, 30}, "",
        &check_box_checked_
    );

    GuiButton(
        Rectangle{(float)(width_ - 125), (float)(height_ - 40), 100, 30}, ""
    ); // returns true when clicked, wire up to save functionality
}

void jrat::Window::update_boxes() {

    mouse_pos_ = GetMousePosition();
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
