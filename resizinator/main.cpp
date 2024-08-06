#include "opencv2/opencv.hpp"
#include "common.h"
#include "test.h"

int main() {
    jrat::test();
    cv::Mat image;
    image = cv::imread("corpobs.png");
    cv::imshow("Original Image", image);
    cv::waitKey(2000);
    WindowTest* window = new WindowTest();
    window->window_test();
}
