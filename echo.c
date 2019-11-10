#include "echo.h"
#include <stdio.h>
#include <stdlib.h>

static int print_args(int argc, char **argv) {
    if (argc <= 0) return 0;
    int err = 0;
    for (int i = 0; i < argc-1; ++i) {
        err = printf("%s ", argv[i]);
        if (err < 0) return EXIT_FAILURE;
    }
    err = printf("%s", argv[argc-1]);
    if (err < 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int echo(int argc, char **argv) {
    int err = print_args(argc, argv);
    if (err == EXIT_FAILURE) return err;
    err = printf("\n");
    if (err < 0) return err;
    return EXIT_SUCCESS;
}

int echo_n(int argc, char **argv) {
    return print_args(argc, argv);
}
