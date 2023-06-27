#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

/**
 * _printf - a function that produces output according to a format
 *
 * @format: a character string composed of zero or more directives
 *
 * Return: the number of characters printed (excluding the null byte)
 */

int _printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int round = 0;

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;

            if (*format == '\0')
                break;

            if (*format == '%')
            {
                write(1, "%", 1);
                round++;
            }
            else if (*format == 'c')
            {
                char c = (char)va_arg(args, int);
                write(1, &c, 1);
                round++;
            }
            else if (*format == 's')
            {
                const char *s = va_arg(args, const char *);
                int length = 0;
                while (s[length] != '\0')
                    length++;

                write(1, s, length);
                round += length;
            }
        }
        else
        {
            write(1, format, 1);
            round++;
        }

        format++;
    }

    va_end(args);

    return (round);
}