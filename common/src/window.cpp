#include "common/window.h"

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
    load_image("C:/PRO-100/jrat/common/resources/JoshBeautifulDrawing.PNG");
    SetWindowSize(img_.width + 100, img_.height + 100);
    while (!WindowShouldClose()) {
        update();
        update_boxes();
        BeginDrawing();

        draw();
        draw_boxes();
        draw_image();
        EndDrawing();
    }
}

void jrat::Window::create_text_box(float x_pos, float y_pos, float width, float height) {
    text_boxes_.emplace_back(TextBox{x_pos, y_pos, width, height});
}

void jrat::Window::load_image(const char *file_name) {
    if (img_.height != 0) {
        throw std::runtime_error("You are dumb, Richard approved!!");
    } else {
        img_ = LoadTexture(file_name);
    }
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
