#include "escape.h"

int main(int argc, char** argv) {
    return echo_e(argc-1, &argv[1]);
}
