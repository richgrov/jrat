#include "common/window.h"

#include <raylib.h>

using namespace jrat;

Window::Window(int width, int height, const std::string &title) {
    InitWindow(width, height, title.c_str());
    SetTargetFPS(60);
}

Window::~Window() {
    CloseWindow();
}

void Window::run() {
    while (!WindowShouldClose()) {
        update();
        update_boxes();
        BeginDrawing();

        draw();
        draw_boxes();
        EndDrawing();
    }
}

void jrat::Window::create_text_box(float x_pos, float y_pos, float width, float height) {
    text_boxes_.emplace_back(TextBox{x_pos, y_pos, width, height});
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
