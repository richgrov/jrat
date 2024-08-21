#define _USE_MATH_DEFINES

#include "common/window.h"
#include "JetBrainsMono.h"
#include "common/image_to_byte.h"

#include <iostream>
#include <cmath>
#include <raylib.h>
#include <stdexcept>
#include <raymath.h>

using namespace jrat;

Window::Window(int width, int height, const std::string &title, const char *image_path) {
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
    image_path_ = const_cast<char *>(image_path);
}

Window::~Window() {
    if (img_.height != 0) {
        UnloadTexture(img_);
    }
    CloseWindow();
}

void Window::run() {
    while (!WindowShouldClose() && running_) {
        update_mouse();
        update();
        update_boxes();
        BeginDrawing();

        draw_ui_bar();
        draw();
        draw_image();
        draw_boxes();
        EndDrawing();
    }
}

void jrat::Window::create_text_box(float x_pos, float y_pos, float width, float height) {
    text_boxes_.emplace_back(TextBox{x_pos, y_pos, width, height});
}

void jrat::Window::create_text_box_left(int box_count) {
    for (int i = 0; i < box_count; i++) {
        text_boxes_.emplace_back(TextBox{
            (float)(125 * text_box_count_ + 10), (float)(height_ - 35), 100, 20,
            text_box_count_ != 0
        });
        text_box_count_++;
    }
}

void jrat::Window::load_image(const char *file_name) {
    if (img_.height != 0) {
        throw std::runtime_error("Can't load more than one image at a time.");
    }
    Image img = imageToBytes(file_name);
    img_ = LoadTextureFromImage(img);
}

void jrat::Window::set_dimensions_and_position() {
    if (img_.height != 0) {
        width_ = GetMonitorWidth(GetCurrentMonitor());
        float temp_height = sqrtf((img_.width * img_.width + img_.height * img_.height)) + 15;
        height_ = temp_height < GetMonitorHeight(GetCurrentMonitor())
                      ? temp_height
                      : GetMonitorHeight(GetCurrentMonitor()) - 50;
    }
    SetWindowSize(width_, height_);
    SetWindowPosition(
        (GetMonitorWidth(GetCurrentMonitor()) - width_) / 2,
        (GetMonitorHeight(GetCurrentMonitor()) - height_) / 2
    );
}

void jrat::Window::close_window() {
    running_ = false;
}

void jrat::Window::load_font() {
    font_ =
        LoadFontFromMemory(".ttf", JetBrainsMono_ttf, sizeof(JetBrainsMono_ttf), 50, nullptr, 0);
}

void jrat::Window::draw_boxes() {

    ClearBackground(DARKGRAY);

    for (int i = 0; i < text_boxes_.size(); i++) {
        GuiTextBox(
            (text_boxes_[i].area()), text_boxes_[i].content_, text_boxes_[i].get_max_length(),
            active_text_box_ == i
        );
        if (text_boxes_[i].has_x()) {
            // no workie
            DrawTextEx(
                font_, "X", Vector2{text_boxes_[i].area().x - 18.5f, (float)(height_ - 36)}, 24.0f,
                1.0f, Color{0, 0, 0, 255}
            );
        }
    }
}

void jrat::Window::draw_image() {
    float offset_width = img_.width / 2;
    float offset_height = img_.height / 2;

    Rectangle source = {0.0f, 0.0f, (float)img_.width, (float)img_.height};
    Rectangle destination = {
        (float)((width_ - img_.width) / 2) + offset_width, (float)((height_ - img_.height) / 2) + offset_height,
        (float)img_.width, (float)img_.height
    };
    Vector2 origin = {offset_width, offset_height};

    DrawTexturePro(img_, source, destination, origin, angle_, Color{255, 255, 255, 255});
}

void jrat::Window::draw_ui_bar() {
    DrawRectangle(0, height_ - 50, width_, 50, Color{255, 255, 255, 255});
    GuiCheckBox(
        Rectangle{(float)(125 * text_box_count_ + 10), (float)(height_ - 40), 30, 30}, "",
        &check_box_checked_
    );

    if ((GuiButton(Rectangle{(float)(width_ - 110), (float)(height_ - 40), 100, 30}, "")
        )) { // returns true when clicked, wire up to save functionality

        save_image();
    }
}

void jrat::Window::update_mouse() {
    mouse_pos_ = GetMousePosition();
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
