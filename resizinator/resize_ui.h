#pragma once
#include "common/window.h"

#include "raylib.h"
#include <string>
namespace jrat {

    class resize_ui : public Window {
    public:
        resize_ui() = default;
        resize_ui(int width, int height, const std::string &title) : Window(width, height, title) {
            font_ = LoadFont("C:/PRO-100/jrat/common/resources/JetBrainsMono.ttf");
        };

        virtual void update() override;
        virtual void draw() override;
        virtual void load_font() override;

    private:

	 //   int width_{ 0 };
     //   int height_{ 0 };
     //   std::string title_;
        Font font_{ GetFontDefault() };
    };
}
