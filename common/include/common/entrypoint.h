#ifdef JRAT_ENTRYPOINT
#error "entrypoint.h included more than once"
#else
#define JRAT_ENTRYPOINT
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <Windows.h>

int run(int argc, char **argv);

#ifdef JRAT_WINMAIN

// NOLINTBEGIN(misc-definitions-in-headers)
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev, LPSTR command, int show_command) {
    // NOLINTEND(misc-definitions-in-headers)
    return run(0, nullptr);
}

#else // if NDEBUG

// NOLINTBEGIN(misc-definitions-in-headers)
int main(int argc, char **argv) {
    // NOLINTEND(misc-definitions-in-headers)
    return run(argc, argv);
}

#endif // else
#endif // if windows
