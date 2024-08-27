#include <iostream>

#include <opencv2/opencv.hpp>

#include "common/entrypoint.h"
#include "rotate_ui.h"
#include "rotatinator.h"

using namespace jrat;

int jrat::run(int argc, char **argv) {
    if (argc < 2 || std::strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }

    std::string image_filepath = argv[1];
    cv::Mat image = cv::imread(image_filepath, cv::IMREAD_UNCHANGED);

    if (image.empty()) {
        std::cout << "Could not find image at: " + image_filepath << std::endl;
        return 0;
    }

    if (argc < 3) {
        RotateUi ui("Rotatinator", image_filepath.c_str(), image);
        ui.run();
        return 0;
    }

    double angle;
    std::string savepath = argc > 3 ? argv[3] : image_filepath;

    try {
        angle = std::stold(argv[2]);
    } catch (const std::exception) {
        std::cout << "angle must be decimal number.";
        return 0;
    }

    write_image(image, angle, savepath);
    return 0;
}
