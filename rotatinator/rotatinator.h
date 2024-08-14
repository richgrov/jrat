#pragma once
#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc.hpp>

namespace jrat {
void rotate(cv::Mat image, cv::Mat &rotated_image, double angle);
} // namespace jrat

void error_panic();