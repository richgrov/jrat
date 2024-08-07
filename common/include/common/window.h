#pragma once

#include <string>

namespace jrat {

class Window {
public:
    explicit Window(int width, int height, const std::string &title);

    ~Window();

    void run();

protected:
    virtual void update() = 0;
    virtual void draw() = 0;
};

} // namespace jrat
