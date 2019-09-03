#include "escape.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool char_isdigit(char c) { return isdigit((unsigned char)c); }

#define ALERT '\a'
#define BACKSPACE '\b'
#define FORMFEED '\f'
#define NEWLINE '\n'
#define NULL_ZERO '\0'
#define CARRIAGE_RETURN '\r'
#define TAB '\t'
#define VTAB '\v'
#define BACKSLASH '\\'

#define MAX_OCTAL 4

#define ESC_CHAR_POS 0

static int escape_c(char *str, char *c, bool *slash_c_seen) {
    int num_digits = 0;
    int octal = 0;
    *slash_c_seen = false;
    switch (str[ESC_CHAR_POS]) {
        case NULL_ZERO:
            return 0;
        case 'a':
            *c = ALERT;
            return 1;
        case 'b':
            *c = BACKSPACE;
            return 1;
        case 'c':
            // "consume" all the remaining characters...
            *slash_c_seen = true;
            return strlen(str);
        case 'f':
            *c = FORMFEED;
            return 1;
        case 'n':
            *c = NEWLINE;
            return 1;
        case 'r':
            *c = CARRIAGE_RETURN;
            return 1;
        case 't':
            *c = TAB;
            return 1;
        case 'v':
            *c = VTAB;
            return 1;
        case '\\':
            // unnecessary: already a backslash at *c
            /* *c = BACKSLASH; */
            return 1;
        case '0':
            while (char_isdigit(str[ESC_CHAR_POS + num_digits])
                    && num_digits < MAX_OCTAL) {
                octal *= 8;
                octal += str[ESC_CHAR_POS + num_digits] - '0';
                ++num_digits;
            }
            *c = (char)octal;
            return num_digits;
        default:
            return -1;
    }
}

static int print_one_at_a_time(int argc, char **argv) {
    int err;
    bool finish = false;
    for (int i = 0; i < argc; ++i) {
        int j = 0;
        char c;
        while ((c = argv[i][j++]) != NULL_ZERO) {
            if (c == BACKSLASH) {
                int consumed = escape_c(&argv[i][j], &c, &finish);
                if (finish) return EXIT_SUCCESS;
                if (consumed < 0) return EXIT_FAILURE;
                j += consumed;
            }
            err = putchar(c);
            if (err == EOF) return EXIT_FAILURE;
        }
        // no space after the very last argument
        if (i < argc-1) {
            err = putchar(' ');
            if (err == EOF) return EXIT_FAILURE;
        }
    }
    err = putchar('\n');
    if (err == EOF) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int echo_e(int argc, char **argv) {
    if (argc <= 0) return EXIT_SUCCESS;
    return print_one_at_a_time(argc, argv);
}
