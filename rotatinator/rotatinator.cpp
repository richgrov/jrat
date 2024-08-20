#include "rotatinator.h"
#include <opencv2/opencv.hpp>
#include <iostream>

void jrat::rotate(cv::Mat image, cv::Mat &rotated_image, double angle) {
    angle = angle * -1;
    cv::Point2f center((image.cols - 1) / 2.0f, (image.rows - 1) / 2.0f);
    cv::Mat rotation_matrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::warpAffine(image, rotated_image, rotation_matrix, image.size());
}

void jrat::print_help() {
    std::cout << "[filepath] [degrees] [rotated image file path]\n";
}

void jrat::write_image(cv::Mat image, double angle, std::string savepath) {
    cv::Mat resized_image;

    jrat::rotate(image, resized_image, angle);
    cv::imwrite(savepath, resized_image);
}