#include "resizinator.h"

#include "resize_ui.h"

#include <opencv2/opencv.hpp>

#include <iostream>

#include "common/entrypoint.h"
#include "common/supported_types.h"

using namespace jrat;

int jrat::run(int argc, char **argv) {
    if (argc < 2 || std::strcmp(argv[1], "--help") == 0) {
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

    if (argc < 4) {
        ResizeUi ui("Resizinator", image_filepath.c_str(), image);
        ui.run();
        return 0;
    }

    int width, height;
    bool keep_aspect_ratio = false;
    std::string savepath = argc > 5 ? argv[5] : image_filepath;

    try {
        width = std::stoi(argv[2]);
        height = std::stoi(argv[3]);
    } catch (const std::exception &) {
        std::cout << "width and height must be integers";
        return 0;
    }

    if (argc > 4 && std::strcmp(argv[4], "-a") == 0) {
        keep_aspect_ratio = true;
    }

    write_image(image, width, height, keep_aspect_ratio, savepath);
    return 0;
}
