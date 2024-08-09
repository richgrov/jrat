#include "resizinator.h"
#include "test.h"
#include "window_example.h"
#include <iostream>
#include <stdlib.h>

using namespace jrat;

int main(int argc, char **argv) {
    // WindowExample example;
    // example.run();

    if (argv[1] == "--help") {
        jrat::error_panic();
        return 0;
    }

    if (argc <= 6) {
        jrat::error_panic();
        return 0;
    }

    std::string image_filepath = argv[1];
    std::string keep_aspect_ratio = argv[2];
    bool keep_original_file = (argv[3] == "-O") ? true : false;
    int width = std::atoi(argv[4]);
    int height = std::atoi(argv[5]);
    std::string new_image_filepath = argv[6];
    cv::Mat resized_image;

    if (keep_aspect_ratio == "-A") {
        resize_aspect_ratio(image_filepath, width);
    } else if (keep_aspect_ratio == "-a") {
        resize(image_filepath, width, height);
    } else {
        error_panic();
        return 0;
    }

    image_filepath = (keep_original_file) ? image_filepath : new_image_filepath;
    jrat::imwrite(image_filepath, resized_image);

    /*WindowTest *window = new WindowTest();
    window->window_test();*/
}
