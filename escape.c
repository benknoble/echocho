#include "escape.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
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

#define MAX_OCTAL 3

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
                while (char_isdigit(str[ESC_CHAR_POS + num_digits])) {
                    octal *= 8;
                    switch(str[ESC_CHAR_POS + num_digits]) {
                        case '0': octal += 0; break;
                        case '1': octal += 1; break;
                        case '2': octal += 2; break;
                        case '3': octal += 3; break;
                        case '4': octal += 4; break;
                        case '5': octal += 5; break;
                        case '6': octal += 6; break;
                        case '7': octal += 7; break;
                        case '8': octal += 8; break;
                        case '9': octal += 9; break;
                    }
                    if (num_digits == MAX_OCTAL) break;
                    ++num_digits;
                }
                str[START] = (char)octal;
                ++str;
                for (int i = 0; i < ESC_CHAR_POS + num_digits; ++i)
                { shift_left_one_char(str); }
                ++escapes_handled;
                break;
            default:
                break;
        }
    }
    return escapes_handled;
}

int interpret_escapes(int argc, char **argv, bool *suppress_newline) {
    *suppress_newline = false;
    for (int i = 0; i < argc; ++i) {
        int err = escape(argv[i], suppress_newline);
        if (err < 0) return err;
        if (*suppress_newline) return i+1;
    }
    return argc;
}
