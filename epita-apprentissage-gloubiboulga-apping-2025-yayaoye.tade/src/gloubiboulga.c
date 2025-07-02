// gloubiboulga_printf.c

#include <unistd.h>     // write
#include <stdarg.h>     // va_list, va_start, va_end
#include <stdlib.h>     // malloc, free

// Fonction utilitaire pour écrire une chaîne
static int put_str(const char *str) {
    int len = 0;
    while (str[len])
        len++;
    return write(STDOUT_FILENO, str, len);
}

// Écris un caractère
static int put_char(char c) {
    return write(STDOUT_FILENO, &c, 1);
}

// Convertit un entier en chaîne décimale (malloc)
// Retourne NULL en cas d'erreur
static char *itoa(int value) {
    char *buffer = malloc(12); // assez grand pour int (-2147483648 + '\0')
    if (!buffer) return NULL;

    int is_negative = (value < 0);
    unsigned int abs_value = is_negative ? (unsigned int)(-value) : (unsigned int)value;

    buffer[11] = '\0';
    int i = 10;

    do {
        buffer[i--] = '0' + (abs_value % 10);
        abs_value /= 10;
    } while (abs_value > 0);

    if (is_negative)
        buffer[i--] = '-';

    // i est à la position avant le début de la chaîne
    // on déplace la chaîne à gauche, au début de buffer

    int start = i + 1;
    int length = 11 - start;

    // décaler la chaîne au début
    for (int j = 0; j <= length; j++) { // y compris '\0'
        buffer[j] = buffer[start + j];
    }

    return buffer;
}


int gloubiboulga(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int total = 0;

    for (size_t i = 0; format[i]; i++) {
        if (format[i] != '%') {
            total += put_char(format[i]);
            continue;
        }

        i++; // saute '%'

        if (format[i] == 's') {
            const char *s = va_arg(args, const char *);
            if (!s) s = "(null)";
            total += put_str(s);
        } else if (format[i] == 'd') {
            int d = va_arg(args, int);
            char *s = itoa(d);
            if (!s) {
                va_end(args);
                return -1;
            }
            total += put_str(s);
            free(s);
        } else if (format[i] == 'c') {
            char c = (char) va_arg(args, int);
            total += put_char(c);
        } else if (format[i] == '%') {
            total += put_char('%');
        } else {
            total += put_char('%');
            total += put_char(format[i]);
        }
    }

    va_end(args);
    return total;
}
