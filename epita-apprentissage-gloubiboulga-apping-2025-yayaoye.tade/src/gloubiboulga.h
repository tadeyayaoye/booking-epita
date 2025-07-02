#ifndef GLOUBIBOULGA_H
#define GLOUBIBOULGA_H

#include <stddef.h>

/**
 * @brief Mini printf maison - affiche sur stdout.
 * 
 * Supported formats:
 *   - %s : string
 *   - %d : signed integer decimal
 *   - %c : character
 *   - %% : literal %
 * 
 * Returns total number of characters printed, or -1 on error.
 */
int gloubiboulga(const char *format, ...);

#endif // GLOUBIBOULGA_H
