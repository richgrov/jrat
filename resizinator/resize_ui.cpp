#include "resize_ui.h"
#include <filesystem>
#include <iostream>

void jrat::resize_ui::update() {

}

void jrat::resize_ui::draw() {
    const Vector2 pos = {width_ / 2, height_ / 2};
    DrawTextEx(font_, "hello world", pos, 50, 1.0f, RED);
}

void jrat::resize_ui::load_font() {
    font_ = LoadFont("C:/PRO-100/jrat/common/resources/JetBrainsMono.ttf");
}
