#pragma once

#include <string>
#include <vector>

#include "stringutil.h"

namespace jrat {

// clang-format off
static std::vector<std::string> supported_types = {
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
    for (std::string type : supported_types) {
        if (to_lowercase(fileName).ends_with(type)) {
            return true;
        }
    }

    return false;
}

} // namespace jrat
