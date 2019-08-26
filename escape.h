#ifndef ESCAPE_H
#define ESCAPE_H

#include <stdbool.h>

int interpret_escapes(int argc, char **argv, bool *suppress_newline);

#endif
