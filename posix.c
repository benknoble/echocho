#include "echo.h"
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc == 1) return 0;
    int err = echo(argc-1, &argv[1]);
    if (err < 0) return EXIT_FAILURE;
    return 0;
}
