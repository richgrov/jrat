#pragma once

#include <string>

#include "stringutil.h"

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

static inline bool is_supported(std::string &fileName) {
    bool supported = false;

    for (std::string type : supported_types) {
        if (to_lowercase(fileName).ends_with(type)) {
            supported = true;
        }
    }

    return supported;
}

} // namespace jrat
