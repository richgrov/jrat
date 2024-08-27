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

namespace {

constexpr float IMAGE_SCREEN_COVERAGE = 0.9f;

} // namespace

Window::Window(const std::string &title, const char *image_path) {
    InitWindow(width_, height_, title.c_str());
    SetTargetFPS(60);
    image_path_ = const_cast<char *>(image_path);

    font_ =
        LoadFontFromMemory(".ttf", JetBrainsMono_ttf, sizeof(JetBrainsMono_ttf), 50, nullptr, 0);

    load_image(image_path);
    set_dimensions_and_position();
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

void jrat::Window::create_text_box_left() {
    float x_pos = 125 * text_box_count_ + 10;
    float y_pos = height_ - 35;

    TextBox text_box = {x_pos, y_pos, 100, 20, text_box_count_ != 0};

    text_boxes_.emplace_back(text_box);
    text_box_count_++;
}

void jrat::Window::create_text_box_left(int box_count) {
    for (int i = 0; i < box_count; i++) {
        create_text_box_left();
    }
}

void jrat::Window::create_text_box_left(const char *label) {
    float x_pos = 125 * text_box_count_ + 10;
    float y_pos = height_ - 35;

    TextBox text_box = {x_pos, y_pos, 100, 20, false};

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
    img_mask_.width = static_cast<float>(img_.width);
    img_mask_.height = static_cast<float>(img_.height);
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
                font_, "X", Vector2{text_boxes_[i].area().x - 18.5f, (float)(height_ - 36)}, 24.0f,
                1.0f, Color{0, 0, 0, 255}
            );
        }
    }
}

void jrat::Window::draw_image() {
    float hypot = sqrtf(static_cast<float>(img_.width * img_.width + img_.height * img_.height));
    // Amount to scale the image by to ensure it stays within bounds of the window + some padding
    float scale = ((height_ - 50) / hypot) * IMAGE_SCREEN_COVERAGE;

    float scaled_width = static_cast<float>(img_.width) * scale;
    float scaled_height = static_cast<float>(img_.height) * scale;

    Vector2 origin = {scaled_width / 2, scaled_height / 2};

    float left = (static_cast<float>(width_) - scaled_width) / 2.f;
    float top = (static_cast<float>(height_ - 50) - scaled_height) / 2.f;

    Rectangle destination = {
        .x = left + origin.x + img_mask_.x * scale,
        .y = top + origin.y + img_mask_.y * scale,
        .width = img_mask_.width * scale,
        .height = img_mask_.height * scale,
    };

    DrawTexturePro(img_, img_mask_, destination, origin, angle_, Color{255, 255, 255, 255});
}

void jrat::Window::draw_ui_bar() {
    DrawRectangle(0, height_ - 50, width_, 50, Color{255, 255, 255, 255});
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
    if ((GuiButton(Rectangle{(float)(width_ - 110), (float)(height_ - 40), 100, 30}, "")
        )) { // returns true when clicked, wire up to save functionality

        save_image();
    }
}

void jrat::Window::update_mouse() {
    mouse_pos_ = GetMousePosition();
}

void jrat::Window::add_checkbox_auto() {
    check_box_checked_.push_back(false);
    Rectangle rect = {
        (float)(125 * text_box_count_ + 10 + 40 * check_box_rects_.size()), (float)(height_ - 40),
        30, 30
    };
    check_box_rects_.push_back(rect);
}

void jrat::Window::add_checkbox(float x, float y) {
    check_box_checked_.push_back(false);
    Rectangle rect = {x, y, 30, 30};
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
