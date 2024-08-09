#pragma once

#include <raylib.h>
#include <string>

namespace jrat {

class Window {
public:
    explicit Window(int width, int height, const std::string &title);

    ~Window();

    void run();

protected:
    virtual void load_font() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    int width_{0};
    int height_{0};
    Font font_{NULL};
};

} // namespace jrat
