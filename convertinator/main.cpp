#include <filesystem>
#include <string>

#include <opencv2/opencv.hpp>

#include "common/entrypoint.h"
#include "common/supported_types.h"

using namespace jrat;

int jrat::run(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "usage: convertinator [filename] [type]";
        return 0;
    }

    std::string file = argv[1];
    std::string new_type = argv[2];
    std::string old_type;

    if (!is_supported(file)) {
        std::cout << "Unsupported input file type.";
        return 0;
    }

    if (!is_supported(new_type)) {
        std::cout << "Unsupported output file type.";
        return 0;
    }

    std::string output_file = file.substr(0, file.find_last_of('.')) + "." + new_type;
    cv::Mat image = cv::imread(file, cv::IMREAD_UNCHANGED);

    if (image.empty()) {
        std::cout << "No file found at " + file;
        return 0;
    }

    cv::imwrite(output_file, image);
    return 0;
}
