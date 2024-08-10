#pragma once
#include "common/ui_framework.h"

#include <string>
namespace jrat {

    class Resize_Ui : public Ui_Frame {
    public:

        Resize_Ui() = default;
        Resize_Ui(int width, int height, const std::string &title) : Ui_Frame(width, height, title) {
            //font_ = LoadFont("C:/PRO-100/jrat/common/resources/JetBrainsMono.ttf");
            create_text_box(10, 570, 100, 20);
            create_text_box(135, 570, 100, 20);
        };

        virtual void load_font() override;

    private:

        Font font_{ GetFontDefault() };
    };
}
