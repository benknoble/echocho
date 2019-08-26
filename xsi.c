#include "echo.h"
#include "escape.h"
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char** argv) {
    if (argc == 1) return 0;
    char **args = &argv[1];
    bool suppress_newline;
    int actual_argc = interpret_escapes(argc-1, args, &suppress_newline);
    if (actual_argc < 0) return EXIT_FAILURE;
    int err;
    if (suppress_newline) {
        err = echo_n(actual_argc, args);
    } else {
        err = echo(actual_argc, args);
    }
    if (err < 0) return EXIT_FAILURE;
    return 0;
}
