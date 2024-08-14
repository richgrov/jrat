#pragma once

#include <string>

namespace jrat {

// clang-format off
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
// clang-format on

} // namespace jrat
