#include "echo_e.h"
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char** argv) {
    return echo_e(argc-1, &argv[1]);
}
