#include "echo_e.h"
#include "echo_n.h"
#include "echo.h"
#include "escape.h"
#include <stdbool.h>
#include <stdlib.h>

int echo_e(int argc, char **argv) {
    bool suppress_newline;
    argc = interpret_escapes(argc, argv, &suppress_newline);
    if (argc < 0) return EXIT_FAILURE;
    if (suppress_newline) {
        return echo_n(argc, argv);
    } else {
        return echo(argc, argv);
    }
}
