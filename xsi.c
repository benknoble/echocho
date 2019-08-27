#include "echo.h"
#include "escape.h"
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char** argv) {
    char **args = &argv[1];
    bool suppress_newline;
    int actual_argc = interpret_escapes(argc-1, args, &suppress_newline);
    if (actual_argc < 0) return EXIT_FAILURE;
    if (suppress_newline) {
        return echo_n(actual_argc, args);
    } else {
        return echo(actual_argc, args);
    }
}
