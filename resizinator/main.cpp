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
    if (argc < 3 || std::strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }

    std::string image_filepath = argv[1];

    if (!is_supported(image_filepath)) {
        std::cout << "Unsupported file type.";
        return 0;
    }

    cv::Mat image = cv::imread(image_filepath, cv::IMREAD_UNCHANGED);

    if (image.empty()) {
        std::cout << "No image was found at: " + image_filepath << std::endl;
        print_help();
        return 0;
    }

    if (std::strcmp(argv[2], "--ui") == 0) {
        ResizeUi ui(800, 600, "Resizinator", image_filepath.c_str(), image);
        ui.run();
        return 0;
    }

    int width, height;
    bool keep_aspect_ratio = false;
    std::string save_path = image_filepath; // maybe allow this to be set?

    try {
        width = std::stoi(argv[2]);
        height = std::stoi(argv[3]);
    } catch (const std::exception &ex) {
        std::cout << "width and height must be integers";
        return 0;
    }

    if (argc > 3 && std::strcmp(argv[4], "-a") == 0) {
        keep_aspect_ratio = true;
    }

    write_image(image, width, height, keep_aspect_ratio, save_path);
}
