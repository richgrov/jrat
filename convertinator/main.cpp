#include "common/stringutil.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>

static std::string supported_types[] = {
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
        std::cout << "usage: convertinator [filename] [type] <remove original (-r)>";
        return 0;
    }

    std::string file = argv[1];
    std::string new_type = argv[2];
    std::string old_type;

    bool input_supported = false;
    bool output_supported = false;

    for (int i = 0; i < size(supported_types); i++) {
        if (jrat::to_lowercase(file).ends_with(supported_types[i])) {
            old_type = supported_types[i];
            input_supported = true;
        }

        if (jrat::to_lowercase(new_type) == supported_types[i]) {
            output_supported = true;
        }
    }

    if (!output_supported) {
        std::cout << "Unsupported output file type.";
        return 0;
    }

    if (!input_supported) {
        std::cout << "Unsupported input file type.";
        return 0;
    }

    if (argc > 3 && argv[3] == "-r") {
        std::filesystem::remove(file);
    }

    std::string output_file = file.substr(0, file.find_last_of('.')) + "." + new_type;
    
    cv::Mat image = cv::imread(file);

    if (image.data == NULL) {
        std::cout << "No file found at " + file;
        return 0;
    }

    cv::imwrite(output_file, image);
}