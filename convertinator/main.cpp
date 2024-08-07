#include "stringutil.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

static std::string supportedTypes[] = {
    "bmp", "dib",
    "jpeg", "jpg", "jpe",
    "jp2",
    "png",
    "webp",
    "pbm",  "pgm",  "ppm", "pxm", "pnm",
    "sr", "ras",
    "tiff", "tif",
    "exr",
    "hdr", "pic"
};

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "usage: convertinator [filename] [type]";
        return 0;
    }

    std::string file = argv[1];
    std::string newType = argv[2];
    std::string oldType;

    bool inputSupported = false;
    bool outputSupported = false;

    for (int i = 0; i < size(supportedTypes); i++) {
        if (endsWith(toLowercase(file), supportedTypes[i])) {
            oldType = supportedTypes[i];
            inputSupported = true;
        }

        if (toLowercase(newType) == supportedTypes[i]) {
            outputSupported = true;
        }
    }

    if (!outputSupported) {
        std::cout << "Unsupported output file type.";
        return 0;
    }

    if (!inputSupported) {
        std::cout << "Unsupported input file type.";
        return 0;
    }

    std::string outputFile = file.substr(0, file.find_last_of('.')) + "." + newType;
    
    cv::Mat image = cv::imread(file);
    cv::imwrite(outputFile, image);
}