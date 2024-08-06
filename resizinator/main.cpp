#include "opencv2/opencv.hpp"
#include "common.h"

int main() {
    jrat::test();
    cv::Mat image;
    image = cv::imread("corpobs.png");
    cv::imshow("Original Image", image);
    cv::waitKey(2000);
}
