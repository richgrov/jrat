#include "resizinator.h"

#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

cv::Mat jrat::resize(std::string filepath, int width, int height) {
    cv::Mat image = cv::imread(filepath, cv::IMREAD_UNCHANGED);
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
    cv::Mat image = cv::imread(filepath, cv::IMREAD_UNCHANGED);
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

void jrat::print_help() {
    std::cout << "usage: resizinator [filepath] --ui\n";
    std::cout << "or resizinator [filepath] [width] [height] <keep aspect ratio (-a)>\n";
}

void jrat::write_image(
    std::string filepath, int width, int height, bool keep_aspect_ratio, std::string savepath
) {
    cv::Mat resized_image = keep_aspect_ratio ? resize_aspect_ratio(filepath, width)
                                              : resize(filepath, width, height);
    imwrite(savepath, resized_image);
}