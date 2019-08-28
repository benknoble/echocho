#include "echo.h"
#include "echo_n.h"
#include <stdlib.h>
#include <stdio.h>

int echo(int argc, char **argv) {
    int ret = echo_n(argc, argv);
    if (ret == EXIT_FAILURE) return EXIT_FAILURE;
    int err = printf("\n");
    if (err < 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
