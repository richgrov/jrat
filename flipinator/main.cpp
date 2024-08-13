#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "usage: flipinator [filename] [direction]";
        return 0;
    }

    std::string file = argv[1];
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

    std::string direction = jrat::to_lowercase(argv[2]);
    int int_direction = 0;

    if (direction == "horizontal" || direction == "h") {
        int_direction = 1;
    } else if (direction != "vertical" && direction != "v") {
        std::cout << "Invalid direction. Use either horizontal or vertical.";
        return 0;
    }

    cv::Mat image = cv::imread(file);

    if (image.data == NULL) {
        std::cout << "No file found at " + file;
        return 0;
    }

    cv::Mat flip;

    cv::flip(image, flip, int_direction);
    cv::imwrite(file, flip);
}