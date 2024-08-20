#pragma once

#include <string>

#include <opencv2/core/mat.hpp>

namespace jrat {

cv::Mat resize(cv::Mat &image, int width, int height);

cv::Mat resize_aspect_ratio(cv::Mat &image, int width);

void imwrite(std::string filepath, const cv::Mat &image);

void print_help();

void write_image(
    cv::Mat &image, int width, int height, bool keep_aspect_ratio, std::string savepath
);

} // namespace jrat
