#ifndef RAGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#endif // !RAGUI_IMPLEMENTATION

#include "rotatinator.h"
#include "rotate_ui.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace jrat;

int main(int argc, char **argv) {
    if (argc < 3 || std::strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }
    
    std::string image_filepath = argv[1];
    cv::Mat image = cv::imread(image_filepath, cv::IMREAD_UNCHANGED);

    if (image.empty()) {
        std::cout << "Could not find image at: " + image_filepath << std::endl;
        return 0;
    }

    if (std::strcmp(argv[2], "--ui") == 0) {
        RotateUi ui(800, 600, "Rotatinator", image_filepath.c_str(), image);
        ui.run();
        return 0;
    }

    double angle;
    std::string savepath = image_filepath; // maybe allow this to be set?

    try {
        angle = std::stold(argv[2]);
    } catch (const std::exception) {
        std::cout << "angle must be decimal number.";
        return 0;
    }

    write_image(image, angle, savepath);
}
