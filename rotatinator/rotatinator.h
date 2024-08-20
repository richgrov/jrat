#pragma once
#include <string>
#include <opencv2/core/mat.hpp>

class cv::Mat;

namespace jrat {

void print_help();
void write_image(cv::Mat image, double angle, std::string savepath);

} // namespace jrat