#include "echo.h"
#include <stdlib.h>

int main(int argc, char** argv) {
    int err = echo(argc-1, &argv[1]);
    if (err < 0) return EXIT_FAILURE;
    return 0;
}
