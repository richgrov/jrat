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

        BeginDrawing();
        ClearBackground(BLACK);
        draw();
        EndDrawing();
    }
}
