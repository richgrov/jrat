#include "resizinator.h"
#include <iostream>

cv::Mat jrat::resize(std::string filepath, int width, int height) {
    cv::Mat image = cv::imread(filepath);
    cv::Mat resized_image;

    cv::Size original_image_size = image.size();
    cv::Size resized_image_size = cv::Size(width, height);

    if (original_image_size.area() < resized_image_size.area()) {
        cv::resize(image, resized_image, cv::Size(width, height), cv::INTER_CUBIC);
    } else {
        cv::resize(image, resized_image, cv::Size(width, height), cv::INTER_LINEAR);
    }

    return resized_image;
}

cv::Mat jrat::resize_aspect_ratio(std::string filepath, int width) {
    cv::Mat image = cv::imread(filepath);
    cv::Mat resized_image;

    int aspect_ratio = image.cols / image.rows;
    int height = aspect_ratio * width;

    cv::Size original_image_size = image.size();
    cv::Size resized_image_size = cv::Size(width, height);

    if (original_image_size.area() < resized_image_size.area()) {
        cv::resize(image, resized_image, cv::Size(width, height), cv::INTER_CUBIC);
    } else {
        cv::resize(image, resized_image, cv::Size(width, height), cv::INTER_LINEAR);
    }

    return resized_image;
}

void jrat::imwrite(std::string filepath, cv::Mat image) {
    std::cout << "wrote to " << filepath << std::endl;
    cv::imwrite(filepath, image);
}

void jrat::error_panic() {
    std::cout << "[filepath] [aspect ratio (-A/-a)] [width] [height] [new "
                 "file path]\n"
                 "-A: enable keep aspect ratio\n"
                 "-a: disable keep aspect ratio\n";
}
