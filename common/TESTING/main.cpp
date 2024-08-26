#define RAYGUI_IMPLEMENTATION
#include "TEST.h"
#include "common/entrypoint.h"

namespace jrat {

int run(int argc, char **argv) {
    TestUI test("hello there", "C:/PRO-100/jrat/common/resources/JoshBeautifulDrawing.png");
    test.run();
    return 0;
}

} // namespace jrat
