#include "echo.h"
#include <string.h>

int main(int argc, char** argv) {
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        // swallow the -n
        return echo_n(argc-2, &argv[2]);
    } else {
        // still print newline
        return echo(argc-1, &argv[1]);
    }
}
