#ifdef JRAT_ENTRYPOINT
#error "entrypoint.h included more than once"
#else
#define JRAT_ENTRYPOINT
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <Windows.h>
#include <iostream>

int run(int argc, char **argv);

#ifdef JRAT_WINMAIN

// NOLINTBEGIN(misc-definitions-in-headers)
int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev, LPSTR command, int show_command) {
    // NOLINTEND(misc-definitions-in-headers)
    char *args[16];
    LPSTR cmd_line = GetCommandLine();

    int argc = 0;
    bool new_arg = true;

    for (char *c = cmd_line; *c != '\0'; ++c) {
        if (*c == ' ') {
            *c = '\0';
            new_arg = true;
        } else if (new_arg) {
            args[argc++] = c;
            if (argc >= sizeof(args)) {
                std::cerr << "remaining args beyond 16 were truncated\n";
            }
            new_arg = false;
        }
    }

    return run(argc, args);
}

#else // if NDEBUG

// NOLINTBEGIN(misc-definitions-in-headers)
int main(int argc, char **argv) {
    // NOLINTEND(misc-definitions-in-headers)
    return run(argc, argv);
}

#endif // else
#endif // if windows
