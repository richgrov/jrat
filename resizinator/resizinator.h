#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <string>

namespace jrat {
cv::Mat resize(std::string filepath, int width, int height);
cv::Mat resize_aspect_ratio(std::string filepath, int width);
void imwrite(std::string filepath, cv::Mat image);
void error_panic();
} // namespace jrat
