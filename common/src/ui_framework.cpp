#include "common/ui_framework.h"

using namespace jrat;

void jrat::Ui_Frame::update() {

    mouse_pos_ = GetMousePosition();

    for (int i = 0; i < text_boxes_.size(); i++) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mouse_pos_, text_boxes_[i].get_area())) {
            active_text_box_ = i;
            break;
        } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !CheckCollisionPointRec(mouse_pos_, text_boxes_[i].get_area())) {
            active_text_box_ = -1;
        }
    }

    if (IsKeyPressed(KEY_TAB)) {
        active_text_box_++;
        active_text_box_ %= text_boxes_.size();
    }
}

void jrat::Ui_Frame::draw() {
    ClearBackground(WHITE);

    for (int i = 0; i < text_boxes_.size(); i++) {
        GuiTextBox(
            text_boxes_[i].get_area(), text_boxes_[i].content_, text_boxes_[i].get_max_length(),
            active_text_box_ == i
        );
    }

    DrawTextEx(font_, "X", Vector2{123, 572}, 16.0f, 1.0f, BLACK);
}

void jrat::Ui_Frame::create_text_box(float x_pos, float y_pos, float width, float height) {
    text_boxes_.emplace_back(TextBox{x_pos, y_pos, width, height});
}
