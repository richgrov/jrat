#pragma once

#include <string>
#include <vector>

namespace jrat {

// clang-format off
const std::vector<std::string> supported_files = {
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
// clang-format on

} // namespace jrat
