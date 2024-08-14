#include "rotatinator.h"
#include <iostream>

void jrat::rotate(cv::Mat image, cv::Mat &rotated_image, double angle) {
    angle = angle * -1;
    cv::Point2f center((image.cols - 1) / 2.0f, (image.rows - 1) / 2.0f);
    cv::Mat rotation_matrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::warpAffine(image, rotated_image, rotation_matrix, image.size());
}

void error_panic() {
    std::cout << "[filepath] [degrees] [rotated image file path]\n";
}
