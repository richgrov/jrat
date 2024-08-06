#include "common.h"
#include "test.h"

int main() {
    jrat::test();
    WindowTest* window = new WindowTest();
    window->window_test();
}
