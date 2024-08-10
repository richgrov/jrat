#pragma once
#include <raygui.h>
#include <string>
#include <array>

namespace jrat {

	struct TextBox {
        public:
            TextBox(float x_pos, float y_pos, float width, float height) : area_{Rectangle{x_pos, y_pos, width, height}} {}

            Rectangle get_area() const { return area_; }
            int get_max_length() const { return max_length_; }
            char content_[9] = {0};

        private:
            Rectangle area_;
            int max_length_{8};
	};
}