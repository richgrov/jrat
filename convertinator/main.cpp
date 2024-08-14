#include <filesystem>
#include <string>

#include <opencv2/opencv.hpp>

#include "common/stringutil.h"
#include "supported_types.h"

using namespace jrat;

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
        if (to_lowercase(file).ends_with(supported_types[i])) {
            old_type = supported_types[i];
            input_supported = true;
        }

        if (to_lowercase(new_type) == supported_types[i]) {
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
    cv::imwrite(output_file, image);
}
