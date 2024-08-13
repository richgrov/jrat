#include <string>

#include <opencv2/opencv.hpp>

#include "common/stringutil.h"

static std::string supported_types[] = {"bmp",  "dib",  "jpeg", "jpg", "jpe", "jp2", "png",
                                        "webp", "pbm",  "pgm",  "ppm", "pxm", "pnm", "sr",
                                        "ras",  "tiff", "tif",  "exr", "hdr", "pic"};

int main(int argc, char *argv[]) {
    if (argc < 5) {
        std::cout << "usage: cropinator [file name] [left] [right] [top] [bottom]";
        return 0;
    }

    std::string file = argv[0];
    std::string left = argv[1];
    std::string right = argv[2];
    std::string top = argv[3];
    std::string bottom = argv[4];

    cv::Mat image = cv::imread(file);

    if (image.data == NULL) {
        std::cout << "No file found at " + file;
        return 0;
    }

    bool supported = false;

    for (std::string type : supported_types) {
        if (jrat::to_lowercase(file).ends_with(type)) {
            supported = true;
        }
    }

    if (!supported) {
        std::cout << "Unsupported file type.";
        return 0;
    }

    cv::Size size = image.size();
    int x, y, width, height;
    
    try {
        x = std::stoi(left);
        y = std::stoi(top);

        width = size.width - std::stoi(right);
        height = size.height - std::stoi(bottom);
    } catch (const std::exception &ex) {
        std::cout << "left, right, top, & bottom must all be integers";
        return 0;
    }

    cv::Mat ROI(image, cv::Rect(x, y, width, height));
    cv::Mat cropped;

    ROI.copyTo(cropped);

    cv::imwrite(file, cropped);
}