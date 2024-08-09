#include "common.h"
#include "opencv2/opencv.hpp"
#include "resize_ui.h"

int main() {
    jrat::test();
    resize_ui *window = new resize_ui(800, 400, "Hello");
    window->make_window();
}
