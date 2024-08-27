#include "common/supported_types.h"
#include <iostream>

#include <opencv2/core/mat.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace dnn = cv::dnn;

namespace {

cv::Mat predict_segment_mask(dnn::Net &net, cv::Mat image) {
    cv::Mat input;
    cv::cvtColor(image, input, cv::COLOR_BGR2RGB);

    cv::Mat blob = dnn::blobFromImage(
        input, 1. / 255., cv::Size(1024, 1024), cv::Scalar(0, 0, 0), false, false
    );
    net.setInput(blob);

    cv::Mat raw_out = net.forward();

    cv::Mat out_img = raw_out.reshape(1, 1024) * 255;
    cv::normalize(out_img, out_img, 0, 255, cv::NORM_MINMAX);
    cv::resize(out_img, out_img, cv::Size(image.cols, image.rows));
    out_img.convertTo(out_img, CV_8U);
    return out_img;
}

} // namespace

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "usage: erasinator <file>\n";
        return 1;
    }

    std::string file = argv[1];
    if (!jrat::is_supported(file)) {
        std::cerr << "Unsupported file type\n";
        return 1;
    }

    cv::Mat image = cv::imread(file, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "No file found at " << file << '\n';
        return 1;
    }

    dnn::Net net = dnn::readNet("model.onnx");

    std::vector<cv::Mat> channels(3);
    cv::split(image, channels);
    channels.push_back(predict_segment_mask(net, image));

    cv::Mat result;
    cv::merge(channels, result);

    cv::imwrite("out.png", result);
}
