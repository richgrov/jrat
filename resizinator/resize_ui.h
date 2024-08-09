#pragma once
#include "raylib.h"
#include <string>

struct resize_ui {
public:
    resize_ui() = default;
	resize_ui(int width, int height){};
    void make_window();

private:

	int width_;
    int height_;
    std::string title_;
    Font font_;
};
