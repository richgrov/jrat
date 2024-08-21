#include "common/entrypoint.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#ifdef JRAT_WINMAIN

#include <iostream>

#include <Windows.h>

// NOLINTBEGIN(misc-definitions-in-headers)
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev, LPSTR command, int show_command) {
    // NOLINTEND(misc-definitions-in-headers)
    char *args[16];
    LPSTR cmd_line = GetCommandLine();

    int argc = 0;
    bool new_arg = true;

    for (char *c = cmd_line; *c != '\0'; ++c) {
        if (new_arg) {
            args[argc++] = c;
            if (argc >= sizeof(args)) {
                std::cerr << "warning: some args were truncated\n";
            }
            new_arg = false;
        } else if (*c == ' ') {
            *c = '\0';
            new_arg = true;
        }
    }

    return jrat::run(argc, args);
}

#else // if NDEBUG

// NOLINTBEGIN(misc-definitions-in-headers)
int main(int argc, char **argv) {
    // NOLINTEND(misc-definitions-in-headers)
    return jrat::run(argc, argv);
}

#endif // else
#endif // if windows
