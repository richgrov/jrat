#include <string>

#include <opencv2/opencv.hpp>

#include "common/stringutil.h"

static std::string supported_types[] = {"bmp",  "dib",  "jpeg", "jpg", "jpe", "jp2", "png",
                                        "webp", "pbm",  "pgm",  "ppm", "pxm", "pnm", "sr",
                                        "ras",  "tiff", "tif",  "exr", "hdr", "pic"};

int main(int argc, char *argv[]) {
    if (argc < 6) {
        std::cout << "usage: cropinator [file name] [left] [right] [top] [bottom]";
        return 0;
    }

    std::string file = argv[1];
    std::string left = argv[2];
    std::string right = argv[3];
    std::string top = argv[4];
    std::string bottom = argv[5];

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

    if (x < 0 || y < 0 || width < 0 || height < 0 || x > size.width || y > size.height ||
        width > size.width || height > size.height) {
        std::cout << "Dimensions are outside the provided image";
        return 0;
    }

    cv::Mat cropped = image(cv::Range(y, height), cv::Range(x, width));
    cv::imwrite(file, cropped);
}