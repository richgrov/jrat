#include "ui.h"

using namespace jrat;

CropUi::CropUi(const char *filepath) : Window(1280, 720, "Resize Image", filepath) {
    load_font();
    load_image(filepath);
    set_dimensions_and_position();
    ui_boxes();
}

void CropUi::ui_boxes() {
    create_text_box_left(4);
}
