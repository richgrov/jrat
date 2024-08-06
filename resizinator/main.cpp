#include "opencv2/opencv.hpp"
#include "test.h"
#include "window_example.h"

using namespace jrat;

int main() {
    WindowExample example;
    example.run();

    cv::Mat image;
    image = cv::imread("corpobs.png");
    cv::imshow("Original Image", image);
    cv::waitKey(2000);
    WindowTest* window = new WindowTest();
    window->window_test();
}
