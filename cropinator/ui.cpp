#include "ui.h"

using namespace jrat;

CropUi::CropUi(const char *filepath) : Window(1280, 720, "Resize Image", filepath) {
    load_font();
    load_image(filepath);
}
