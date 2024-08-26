#include "common/entrypoint.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#ifdef JRAT_WINMAIN

#include <Windows.h>
#include <stdlib.h>

// NOLINTBEGIN(misc-definitions-in-headers)
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev, LPSTR command, int show_command) {
    // NOLINTEND(misc-definitions-in-headers)
    return jrat::run(__argc, __argv);
}

#else // if NDEBUG

// NOLINTBEGIN(misc-definitions-in-headers)
int main(int argc, char **argv) {
    // NOLINTEND(misc-definitions-in-headers)
    return jrat::run(argc, argv);
}

#endif // else
#endif // if windows
