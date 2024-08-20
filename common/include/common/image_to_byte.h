#pragma once
#include <opencv2/opencv.hpp>
#include <raylib.h>
#include <vector>

namespace jrat {

typedef unsigned char byte;

static inline Image imageToBytes(const char *filepath) {
    cv::Mat image = cv::imread(filepath, cv::IMREAD_UNCHANGED);
    if (image.empty()) {
        throw new std::runtime_error("OpenCV couldn't read file");
    }
    std::vector<byte> buffer;
    if (!cv::imencode(".png", image, buffer)) {
        throw new std::runtime_error("OpenCV couln't encode file");
    }
    Image image_ray = LoadImageFromMemory(".png", buffer.data(), buffer.size());
    if (image_ray.data == nullptr) {
        throw new std::runtime_error("Raylib has failed to convert to image.");
    }
    return image_ray;
}

} // namespace jrat
