#define RAYGUI_IMPLEMENTATION

#include <string>

#include <opencv2/opencv.hpp>

#include "common/entrypoint.h"
#include "common/supported_types.h"
#include "ui.h"

int jrat::run(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "usage: cropinator <file name> [left] [right] [top] [bottom]\n";
        return 1;
    }

    std::string file = argv[1];
    if (!jrat::is_supported(file)) {
        std::cout << "Unsupported file type.";
        return 0;
    }

    cv::Mat image = cv::imread(file, cv::IMREAD_UNCHANGED);

    if (image.empty()) {
        std::cout << "No file found at " + file;
        return 0;
    }

    if (argc < 6) {
        CropUi ui(file.c_str(), std::move(image));
        ui.run();
        return 0;
    }

    cv::Size size = image.size();
    int x, y, width, height;

    try {
        x = std::stoi(argv[2]);
        y = std::stoi(argv[4]);

        width = size.width - std::stoi(argv[3]);
        height = size.height - std::stoi(argv[5]);
    } catch (const std::exception &ex) {
        std::cout << "left, right, top, & bottom must all be integers";
        return 0;
    }

    if (x < 0 || y < 0 || width < 0 || height < 0 || x > size.width || y > size.height ||
        width > size.width || height > size.height) {
        std::cout << "Dimensions are outside the provided image";
        return 0;
    }

    std::string output_file = argc > 6 ? argv[6] : file;

    cv::Mat cropped = image(cv::Range(y, height), cv::Range(x, width));
    cv::imwrite(output_file, cropped);
    return 0;
}
