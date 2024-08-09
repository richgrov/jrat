#pragma once
#include "raylib.h"
#include <string>

struct resize_ui {
public:
    resize_ui() = default;
    resize_ui(int width, int height, std::string title)
        : 
        width_{width}, 
        height_{height},
        title_{title}
    {};
    void make_window();

private:

	int width_{ 0 };
    int height_{ 0 };
    std::string title_;
    //Font font_{ GetFontDefault() };
};
