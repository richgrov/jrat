#pragma once

#include <stdexcept>

#include <raygui.h>
#include <stdexcept>

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

        // empties textbox to prevent already existing numbers from being displayed
        std::memset(content_, 0, sizeof(content_));

        for (int i = 0; i < string.size(); i++) {
            content_[i] = string[i];
        }
    }

    void check_is_number() {
        for (int i = 0; i < strlen(content_); i++) {
            if (!std::isdigit(content_[i])) {
                content_[i] = '\0';
                return;
            }
        }
    }

private:
    bool has_x_{false};
    Rectangle area_;
    int max_length_{8};
};
} // namespace jrat
