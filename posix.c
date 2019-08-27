#include "echo.h"

int main(int argc, char** argv) {
    return echo(argc-1, &argv[1]);
}
