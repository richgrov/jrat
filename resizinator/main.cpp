#ifndef RAGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#endif // !RAGUI_IMPLEMENTATION

#include "resizinator.h"

#include "resize_ui.h"

#include <opencv2/opencv.hpp>

#include <iostream>

#include "common/supported_types.h"

using namespace jrat;

int main(int argc, char **argv) {
    if (std::strcmp(argv[1], "--help") == 0) {
        jrat::error_panic();
        return 0;
    }

    if (argc == 2 || argc == 1) {
        ResizeUi ui(800, 600, "hello", "C:/PRO-100/jrat/common/resources/JoshBeautifulDrawing.PNG");
        ui.run();
        return 0;
    }

    if (argc < 5 || argc > 6) {
        error_panic();
        return 0;
    }

    std::string image_filepath = argv[1];

    if (!is_supported(image_filepath)) {
        std::cout << "Unsupported file type.";
        return 0;
    }

    cv::Mat image = cv::imread(image_filepath);

    if (image.empty()) {
        std::cout << "No image was found at: " + image_filepath << std::endl; 
        error_panic();
        return 0; 
    }

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
