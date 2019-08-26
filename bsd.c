#include "echo.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc == 1) return 0;
    int err;
    if (strcmp(argv[1], "-n") == 0) {
        // swallow the -n
        err = echo_n(argc-2, &argv[2]);
    } else {
        // still print newline
        err = echo(argc-1, &argv[1]);
    }
    if (err < 0) return EXIT_FAILURE;
    return 0;
}
