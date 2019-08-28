#include "escape.h"
#include "echo.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void shift_left_one_char(char *str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        str[i] = str[i+1];
    }
}

static bool char_isdigit(char c) { return isdigit((unsigned char)c); }

#define ALERT '\a'
#define BACKSPACE '\b'
#define FORMFEED '\f'
#define NEWLINE '\n'
#define CARRIAGE_RETURN '\r'
#define TAB '\t'
#define VTAB '\v'
#define BACKSLASH '\\'

#define MAX_OCTAL 4

#define START 0
#define ESC_CHAR_POS 1
#define ESC_MIN_LEN 2

static int escape(char *str, bool *suppress_newline) {
    int escapes_handled = 0;
    while ((str = strchr(str, BACKSLASH)) != NULL) {
        if (strnlen(str, ESC_MIN_LEN) < ESC_MIN_LEN) break;
        int num_digits = 0;
        int octal = 0;
        switch (str[ESC_CHAR_POS]) {
            case 'a':
                str[START] = ALERT;
                ++str;
                shift_left_one_char(str);
                ++escapes_handled;
                break;
            case 'b':
                str[START] = BACKSPACE;
                ++str;
                shift_left_one_char(str);
                ++escapes_handled;
                break;
            case 'c':
                *suppress_newline = true;
                // clear out this arg
                str[START] = '\0';
                return ++escapes_handled;
                break;
            case 'f':
                str[START] = FORMFEED;
                ++str;
                shift_left_one_char(str);
                ++escapes_handled;
                break;
            case 'n':
                str[START] = NEWLINE;
                ++str;
                shift_left_one_char(str);
                ++escapes_handled;
                break;
            case 'r':
                str[START] = CARRIAGE_RETURN;
                ++str;
                shift_left_one_char(str);
                ++escapes_handled;
                break;
            case 't':
                str[START] = TAB;
                ++str;
                shift_left_one_char(str);
                ++escapes_handled;
                break;
            case 'v':
                str[START] = VTAB;
                ++str;
                shift_left_one_char(str);
                ++escapes_handled;
                break;
            case '\\':
                // unnecessary: already a backslash at str[START]
                /* str[START] = BACKSLASH; */
                ++str;
                shift_left_one_char(str);
                ++escapes_handled;
                break;
            case '0':
                while (char_isdigit(str[ESC_CHAR_POS + num_digits])
                        && num_digits < MAX_OCTAL) {
                    octal *= 8;
                    octal += str[ESC_CHAR_POS + num_digits] - '0';
                    ++num_digits;
                }
                str[START] = (char)octal;
                ++str;
                for (int i = 0; i < num_digits; ++i)
                { shift_left_one_char(str); }
                ++escapes_handled;
                break;
            default:
                break;
        }
    }
    return escapes_handled;
}

static int interpret_escapes(int argc, char **argv, bool *suppress_newline) {
    *suppress_newline = false;
    for (int i = 0; i < argc; ++i) {
        int err = escape(argv[i], suppress_newline);
        if (err < 0) return err;
        if (*suppress_newline) return i+1;
    }
    return argc;
}

int echo_e(int argc, char **argv) {
    if (argc <= 0) return EXIT_SUCCESS;
    bool suppress_newline;
    argc = interpret_escapes(argc, argv, &suppress_newline);
    if (argc < 0) return EXIT_FAILURE;
    if (suppress_newline) {
        return echo_n(argc, argv);
    } else {
        return echo(argc, argv);
    }
}
