#include "rotatinator.h"
#include <iostream>

int main(int argc, char **argv) {
    if (std::strcmp(argv[1], "--help") == 0) {
        error_panic();
        return 0;
    }

    if (argc < 2) {
        error_panic();
        return 0;
    }

    std::string image_filepath = argv[1];

    cv::Mat image = cv::imread(image_filepath);
    if (image.empty()) {
        std::cout << "Could not find image at: " + image_filepath << std::endl;
        return 0;
    }

    double angle = std::atof(argv[2]) * -1;
    std::string resized_image_filepath;

    if (argc == 4) {
        resized_image_filepath = argv[3];
    }

    cv::Mat resized_image;
    jrat::rotate(image, resized_image, angle);
    cv::imwrite(resized_image_filepath, resized_image);
}