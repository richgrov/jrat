#include "common/stringutil.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "usage: flipinator [filename] [direction]";
        return 0;
    }

    std::string file = argv[1];
    int int_direction = 0;

    if (direction == "horizontal" || direction == "h") {
        int_direction = 1;
    } else if (direction != "vertical" && direction != "v") {
        std::cout << "Invalid direction. Use either horizontal or vertical.";
        return 0;
    }

    cv::Mat image = cv::imread(file);
    cv::Mat flip;

    cv::flip(image, flip, int_direction);
    cv::imwrite(file, flip);
}