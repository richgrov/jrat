#pragma once
#include "common/window.h"


#include <string>
namespace jrat {

    class Resize_Ui : public Window {
    public:

        Resize_Ui() = default;
        Resize_Ui(int width, int height, const std::string &title) : Window(width, height, title) {
            //font_ = LoadFont("C:/PRO-100/jrat/common/resources/JetBrainsMono.ttf");
            create_text_box(10, 570, 100, 20);
            create_text_box(135, 570, 100, 20);
        };

        virtual void load_font() override;
        virtual void update() override;
        virtual void draw() override;

    private:

        Font font_{ GetFontDefault() };
    };
}
