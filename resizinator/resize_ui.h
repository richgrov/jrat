#pragma once
#include "common/window.h"


#include <string>
namespace jrat {

    class ResizeUi : public Window {
    public:

        ResizeUi() = default;
        ResizeUi(int width, int height, const std::string &title);

        virtual void load_font() override;
        virtual void update() override;
        virtual void draw() override;

    private:

        Font font_{ GetFontDefault() };
    };
}
