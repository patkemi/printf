#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


/**
 * Converts a decimal number to its binary representation.
 * The resulting binary string is dynamically allocated and must be freed by the caller.
 *
 * @param decimal The decimal number to convert.
 * @return The binary representation of the decimal number as a dynamically allocated string.
 */
char *decimal_to_binary(int decimal);

/**
 * _printf - Custom printf function that produces output according to a format.
 *
 * @format: A format string containing zero or more directives.
 *          The format can include conversion specifiers and flags.
 *          Supported conversion specifiers: c, s, %, d, i, u, o, x, X, b, S, p, r, R
 *
 * Return: The number of characters printed (excluding the null byte used to end output to strings).
 */
int _printf(const char *format, ...);

#endif /* MAIN_H */

