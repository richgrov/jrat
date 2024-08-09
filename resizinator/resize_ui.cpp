#include "resize_ui.h"
#include <filesystem>
#include <iostream>

void resize_ui::make_window() {
    // Initialization
    const char *message = "Hello world! It's great to be here.";
    const int fontSize = 40;
    const float msgSpacing = 1.0f;

    InitWindow(width_, height_, title_.c_str());

    // NOTE: The following only works after calling InitWindow() (i.e,. RayLib is initialized)
    const Font font = LoadFont("C:/PRO-100/jrat/common/resources/JetBrainsMono.ttf");
    const Vector2 msgSize = MeasureTextEx(font, message, fontSize, msgSpacing);
    const Vector2 msgPos =
        Vector2{(width_ - msgSize.x) / 2, (height_ - msgSize.y) / 2};

    SetTargetFPS(60);

    // Main loop
    while (!WindowShouldClose()) {

        // Update the display
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextEx(font, message, msgPos, fontSize, msgSpacing, RED);
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
}
