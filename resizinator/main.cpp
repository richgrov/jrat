#ifndef RAGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#endif // !RAGUI_IMPLEMENTATION

#include "resize_ui.h"
#include "resizinator.h"

using namespace jrat;

int main(int argc, char **argv) {
    if (std::strcmp(argv[1], "--help") == 0) {
        jrat::error_panic();
        return 0;
    }

    if (argc == 2 || argc == 1) {
        ResizeUi ui(800, 600, "hello");
        ui.run();
        return 0;
    }

    if (argc < 5 || argc > 6) {
        error_panic();
        return 0;
    }

    std::string image_filepath = argv[1];
    std::string keep_aspect_ratio = argv[2];
    int width = std::atoi(argv[3]);
    int height = std::atoi(argv[4]);
    std::string new_image_filepath;
    if (argc == 6) {
        new_image_filepath = argv[5];
    }
    cv::Mat resized_image;

    if (keep_aspect_ratio == "-A") {
        resized_image = resize_aspect_ratio(image_filepath, width);
    } else if (keep_aspect_ratio == "-a") {
        resized_image = resize(image_filepath, width, height);
    } else {
        error_panic();
        return 0;
    }

    image_filepath = (argc == 5) ? image_filepath : new_image_filepath;
    imwrite(image_filepath, resized_image);
}
