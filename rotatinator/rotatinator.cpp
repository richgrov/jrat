#include "rotatinator.h"
#include <iostream>

void jrat::rotate_90_clockwise(cv::Mat image, cv::Mat &rotated_image) {
    cv::rotate(image, rotated_image, cv::ROTATE_90_CLOCKWISE);
}

void jrat::rotate_90_counter_clockwise(cv::Mat image, cv::Mat &rotated_image) {
    cv::rotate(image, rotated_image, cv::ROTATE_90_COUNTERCLOCKWISE);
}

void jrat::rotate_180(cv::Mat image, cv::Mat &rotated_image) {
    cv::rotate(image, rotated_image, cv::ROTATE_180);
}

void jrat::rotate(cv::Mat image, cv::Mat &rotated_image, double angle) {
    cv::Point2f center((image.cols - 1) / 2.0f, (image.rows - 1) / 2.0f);
    cv::Mat rotation_matrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::warpAffine(image, rotated_image, rotation_matrix, image.size());
}

void error_panic() {
    std::cout << "[filepath] [degrees] [rotated image file path]\n";
}
