#include <stdio.h>

#define MAXCHAR 100

void escape(const char from[], char to[]);
void unescape(const char from[], char to[]);

// see page 38 for list of all escape sequences;
// have not done escape sequences for octal and hexadecimal numbers.
int main(void) {
    char escaped[MAXCHAR];
    char unescaped[MAXCHAR];

    char s[] = "hello\tworld\n\r\?\'\"?";

    printf("before: %s\n", s);
    escape(s, escaped);
    printf("after: %s\n", escaped);
    unescape(escaped, unescaped);
    printf("back to before: %s\n", unescaped);
}

// parses escape sequences as two printable chars; e.g. '\t' --> '\\' and 't'
void escape(const char from[], char to[]) {
    int i, j;
    i = j = 0;
    while (from[i] !='\0') {
        switch (from[i]) {
            case '\a':  // alert (bell)
                to[j++] = '\\';
                to[j] = 'a';
                break;
            case 'b':   // backspace
                to[j++] = '\\';
                to[j] = 'b';
                break;
            case '\f':  // formfeed
                to[j++] = '\\';
                to[j] = 'f';
                break;
            case '\n':  // newline
                to[j++] = '\\';
                to[j] = 'n';
                break;
            case '\r':   // carriage return
                to[j++] = '\\';
                to[j] = 'r';
                break;
            case '\t':  // horizontal tab
                to[j++] = '\\';
                to[j] = 't';
                break;
            case '\v':  // vertical tab
                to[j++] = '\\';
                to[j] = 'v';
                break;
            case '\\':  // backslash
                to[j++] = '\\';
                to[j] = '\\';
                break;
            case '\?':  // question mark
                to[j++] = '\\';
                to[j] = '?';
                break;
            case '\'':  // single quote
                to[j++] = '\\';
                to[j] = '\'';
                break;
            case '\"':  // double quote
                to[j++] = '\\';
                to[j] = '"';
                break;
            default:
                to[j] = from[i];
                break;
        }

        i++;
        j++;
    }

    to[j] = '\0';
}

// parses explicitly printed escape sequences into original char
void unescape(const char from[], char to[]) {
    int i, j;
    i = j = 0;
    while (from[i] !='\0') {
        if (from[i] == '\\') {
            i++;
            switch (from[i]) {
                case 'a':  // alert (bell)
                    to[j] = '\a';
                    break;
                case 'b':   // backspace
                    to[j] = '\b';
                    break;
                case 'f':  // formfeed
                    to[j] = '\f';
                    break;
                case 'n':  // newline
                    to[j] = '\n';
                    break;
                case 'r':   // carriage return
                    to[j] = '\r';
                    break;
                case 't':  // horizontal tab
                    to[j] = '\t';
                    break;
                case 'v':  // vertical tab
                    to[j] = '\v';
                    break;
                case '\\':  // backslash
                    to[j] = '\\';
                    break;
                case '?':  // question mark
                    to[j] = '?';
                    break;
                case '\'':  // single quote
                    to[j] = '\'';
                    break;
                case '"':  // double quote
                    to[j] = '"';
                    break;
                default:
                    break;
            }
        } else {
            to[j] = from[i];
        }
        i++;
        j++;
    }

    to[j] = '\0';
}