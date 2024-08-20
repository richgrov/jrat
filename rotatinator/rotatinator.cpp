#include "rotatinator.h"
#include <iostream>
#include <opencv2/opencv.hpp>

void jrat::print_help() {
    std::cout << "[filepath] [degrees] [rotated image file path]\n";
}

void jrat::write_image(cv::Mat image, double angle, std::string savepath) {
    cv::Mat rotated_image;
    // image to rotate in the center
    cv::Point2f center((image.cols - 1) / 2.0f, (image.rows - 1) / 2.0f);
    cv::Mat rotation_matrix = cv::getRotationMatrix2D(center, -angle, 1.0);

    // get the bounding box
    cv::Rect2f bounding_box = cv::RotatedRect(cv::Point2f(), image.size(), angle).boundingRect2f();

    rotation_matrix.at<double>(0, 2) += bounding_box.width / 2.0 - image.cols / 2.0;
    rotation_matrix.at<double>(1, 2) += bounding_box.height / 2.0 - image.rows / 2.0;

    // ROTATE!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    cv::warpAffine(image, rotated_image, rotation_matrix, bounding_box.size());
    cv::imwrite(savepath, rotated_image);
}
