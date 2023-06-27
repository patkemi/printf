#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/** * Custom printf function that writes formatted output to the
 *  standard output stream. 
 * @param format The format string containing directives and optional arguments. 
 * Conversion specifiers in the format string are replaced by the 
 * corresponding formatted values from the additional arguments.
 * The format string can also include optional flags, width,
 * precision, and length modifiers to control the formatting.
 * Unsupported or invalid format specifiers are treated as
 * ordinary characters and copied directly to the output.
 * @param ... Additional arguments to be formatted and printed. 
 * @return The number of characters printed (excluding the null
 *  byte used to end output to strings).
 *  If an error occurs, a negative value is returned. */

int _printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[BUFFER_SIZE];
    int count = 0;
    int buffer_index = 0;
    const char *ch;

    for (ch = format; *ch != '\0'; ++ch)
     {
        if (*ch == '%')
         {
            // Handle the conversion specifiers
            int flag_plus = 0;
            int flag_space = 0;
            int flag_hash = 0;
            int flag_zero = 0;

            // Process flags
            while (1)
             {
                ++ch;
                if (*ch == '+')
                    flag_plus = 1;
                else if (*ch == ' ')
                    flag_space = 1;
                else if (*ch == '#')
                    flag_hash = 1;
                else if (*ch == '0')
                    flag_zero = 1;
                else
                    break;
            }

            // Handle the length modifiers
            int length_modifier = 0;
            while (1)
             {
                if (*ch == 'l' || *ch == 'h')
                 {
                    length_modifier = *ch;
                    ++ch;
                } else
                 {
                    break;
                }
            }

            // Handle the conversion specifier
            switch (*ch)
             {
            case 'c':
             {
                    char c = (char)va_arg(args, int);
                    buffer[buffer_index++] = c;
                    count++;
                    break;
            }
            case 's':
             {
                    const char *str = va_arg(args, const char *);
                    while (*str != '\0')
                     {
                        buffer[buffer_index++] = *str++;
                        count++;
                        if (buffer_index == BUFFER_SIZE - 1)
                         {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    }
                    break;
            }
            case 'S':
             {
                    const unsigned char *str = (const unsigned char *)va_arg(args, const char *);
                    while (*str != '\0') 
                    {
                        if (*str < 32 || *str >= 127)
                         {
                            buffer[buffer_index++] = '\\';
                            buffer[buffer_index++] = 'x';
                            buffer[buffer_index++] = ((*str >> 4) < 10) ? ((*str >> 4) + '0') : ((*str >> 4) + 'A' - 10);
                            buffer[buffer_index++] = ((*str & 0x0F) < 10) ? ((*str & 0x0F) + '0') : ((*str & 0x0F) + 'A' - 10);
                            count += 4;
                        } else 
                        {
                            buffer[buffer_index++] = *str;
                            count++;
                        }
                        str++;
                        if (buffer_index == BUFFER_SIZE - 1)
                         {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    }
                    break;
            }
            case 'p':
            {
                    void *ptr = va_arg(args, void *);
                    int num_chars = sprintf(buffer + buffer_index, "%p", ptr);
                    count += num_chars;
                    buffer_index += num_chars;
                    if (buffer_index >= BUFFER_SIZE - 1) 
                    {
                        write(STDOUT_FILENO, buffer, buffer_index);
                        buffer_index = 0;
                    }
                    break;
            }
            case '%':
                    buffer[buffer_index++] = '%';
                    count++;
                    if (buffer_index == BUFFER_SIZE - 1) 
                    {
                        write(STDOUT_FILENO, buffer, buffer_index);
                        buffer_index = 0;
                    }
                    break;
                
            case 'd':
            case 'i': 
            {
                    if (length_modifier == 'l') 
                    {
                        long num = va_arg(args, long);
                        int num_chars = sprintf(buffer + buffer_index, "%+ld", num);
                        if (flag_space && !flag_plus) {
                            buffer[buffer_index] = (num >= 0) ? ' ' : '-';
                            num_chars++;
                        
                    }
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1)
                        {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    } else if (length_modifier == 'h') 
                    {
                        int num = (short)va_arg(args, int);
                        int num_chars = sprintf(buffer + buffer_index, "%+hd", num);
                        if (flag_space && !flag_plus) 
                        {
                            buffer[buffer_index] = (num >= 0) ? ' ' : '-';
                            num_chars++;
                        }
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1) {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    } else {
                        int num = va_arg(args, int);
                        int num_chars = sprintf(buffer + buffer_index, "%+d", num);
                        if (flag_space && !flag_plus) {
                            buffer[buffer_index] = (num >= 0) ? ' ' : '-';
                            num_chars++;
                        }
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1) {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    }
                    break;
            }
            case 'u': 
            {
                    if (length_modifier == 'l') 
                    {
                        unsigned long num = va_arg(args, unsigned long);
                        int num_chars = sprintf(buffer + buffer_index, "%lu", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1) 
                        {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    } else if (length_modifier == 'h')
                     {
                        unsigned int num = (unsigned short)va_arg(args, int);
                        int num_chars = sprintf(buffer + buffer_index, "%hu", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1)
                         {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    } else
                     {
                        unsigned int num = va_arg(args, unsigned int);
                        int num_chars = sprintf(buffer + buffer_index, "%u", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1) 
                        {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    }
                    break;
            }
            case 'o': 
            {
                    if (length_modifier == 'l') 
                    {
                        unsigned long num = va_arg(args, unsigned long);
                        int num_chars = sprintf(buffer + buffer_index, "%#lo", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1) 
                        {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    } else if (length_modifier == 'h') 
                    {
                        unsigned int num = (unsigned short)va_arg(args, int);
                        int num_chars = sprintf(buffer + buffer_index, "%#ho", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1)
                         {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    } else 
                    {
                        unsigned int num = va_arg(args, unsigned int);
                        int num_chars = sprintf(buffer + buffer_index, "%#o", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1)
                         {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    }
                    break;
            }
            case 'x':
             {
                    if (length_modifier == 'l') 
                    {
                        unsigned long num = va_arg(args, unsigned long);
                        int num_chars = sprintf(buffer + buffer_index, "%#lx", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1) 
                        {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    } else if (length_modifier == 'h')
                     {
                        unsigned int num = (unsigned short)va_arg(args, int);
                        int num_chars = sprintf(buffer + buffer_index, "%#hx", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1) {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    } else
                     {
                        unsigned int num = va_arg(args, unsigned int);
                        int num_chars = sprintf(buffer + buffer_index, "%#x", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1) 
                        {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    }
                    break;
            }
            case 'X':
            {
                    if (length_modifier == 'l') 
                    {
                        unsigned long num = va_arg(args, unsigned long);
                        int num_chars = sprintf(buffer + buffer_index, "%#lX", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1) 
                        {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    } else if (length_modifier == 'h')
                     {
                        unsigned int num = (unsigned short)va_arg(args, int);
                        int num_chars = sprintf(buffer + buffer_index, "%#hX", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1)
                         {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    } else 
                    {
                        unsigned int num = va_arg(args, unsigned int);
                        int num_chars = sprintf(buffer + buffer_index, "%#X", num);
                        count += num_chars;
                        buffer_index += num_chars;
                        if (buffer_index >= BUFFER_SIZE - 1)
                         {
                            write(STDOUT_FILENO, buffer, buffer_index);
                            buffer_index = 0;
                        }
                    }
                    break;
            }
            default:
                    buffer[buffer_index++] = *ch;
                    count++;
                    if (buffer_index == BUFFER_SIZE - 1) 
                    {
                        write(STDOUT_FILENO, buffer, buffer_index);
                        buffer_index = 0;
                    }
        }
        } else 
        {
            buffer[buffer_index++] = *ch;
            count++;
            if (buffer_index == BUFFER_SIZE - 1) 
            {
                write(STDOUT_FILENO, buffer, buffer_index);
                buffer_index = 0;
            }
        }
    }

    if (buffer_index > 0) 
    {
        write(STDOUT_FILENO, buffer, buffer_index);
    }

    va_end(args);

    return count;
}
