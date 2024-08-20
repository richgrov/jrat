#pragma once
#include <opencv2/opencv.hpp>
#include <raylib.h>
#include <vector>

namespace jrat {

typedef unsigned char byte;

static inline Image imageToBytes(const char *filepath) {
    cv::Mat image = cv::imread(filepath, cv::IMREAD_UNCHANGED);
    if (image.empty()) {
        std::cout << "empty image" << std::endl;
    }
    std::vector<byte> buffer;
    if (!cv::imencode(".png", image, buffer)) {
        std::cerr << "no image D:" << std::endl;
    }
    Image image_ray = LoadImageFromMemory(".png", buffer.data(), buffer.size());
    if (image_ray.data == nullptr) {
        std::cerr << "no image" << std::endl;
    }
    std::cout << buffer.size() << std::endl;
    std::cout << image_ray.width << " " << image_ray.height << std::endl;
    return image_ray;
}

} // namespace jrat
