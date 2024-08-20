#pragma once

#include <raygui.h>

namespace jrat {

struct TextBox {
public:
    TextBox(float x_pos, float y_pos, float width, float height)
        : area_{Rectangle{x_pos, y_pos, width, height}} {}
    TextBox(float x_pos, float y_pos, float width, float height, bool has_x)
        : area_{Rectangle{x_pos, y_pos, width, height}}, has_x_{has_x} {}

    Rectangle &area() {
        return area_;
    }
    int get_max_length() const {
        return max_length_;
    }
    bool has_x() const {
        return has_x_;
    }
    char content_[9] = {0};

    void set_content(std::string string) {
        if (string.size() > max_length_) {
            throw std::runtime_error("Content size longer than max size.");
        }

        for (int i = 0; i < string.size(); i++) {
            content_[i] = string[i];
        }
    }

private:
    bool has_x_{false};
    Rectangle area_;
    int max_length_{8};
};
} // namespace jrat
