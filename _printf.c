#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

/**
 * _printf - Custom implementation of printf function
 * @format: Format string
 *
 * Return: Number of characters printed (excluding the 
 * null byte used to end output to strings)
 */
int _printf(const char *format, ...)
{
	char buffer[1024];
	int buffer_index = 0;
	int count = 0;

	va_list args;
	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				break;
			if (*format == '%')
			{
				buffer[buffer_index++] = '%';
				count++;
				format++;
				continue;
			}

			int flag_zero_padding = 0;
			int flag_left_align = 0;

			/* Check for flag characters */
			while (*format == '0' || *format == '-')
			{
				if (*format == '0')
					flag_zero_padding = 1;
				else if (*format == '-')
					flag_left_align = 1;
				format++;
			}

			/* Field width */
			int width = 0;
			if (*format >= '1' && *format <= '9')
			{
				width = *format - '0';
				format++;
			}

			/* Precision */
			int precision = -1;
			if (*format == '.')
			{
				format++;
				if (*format >= '0' && *format <= '9')
				{
					precision = 0;
					while (*format >= '0' && *format <= '9')
					{
						precision = precision * 10 + (*format - '0');
						format++;
					}
				}
			}

			/* Conversion specifier */
			switch (*format)
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
					char *str = va_arg(args, char *);
					if (str == NULL)
						str = "(null)";

					int str_length = strlen(str);
					int available_space = sizeof(buffer) - buffer_index - 1;

					if (!flag_left_align)
					{
						/* Padding with spaces */
						if (width > str_length)
						{
							int padding = width - str_length;
							while (padding-- > 0 && buffer_index < sizeof(buffer) - 1)
							{
								buffer[buffer_index++] = ' ';
								count++;
							}
						}
					}

					for (int i = 0; i < str_length; i++)
					{
						buffer[buffer_index++] = str[i];
						count++;
					}

					if (flag_left_align)
					{
						/* Padding with spaces */
						if (width > str_length)
						{
							int padding = width - str_length;
							while (padding-- > 0 && buffer_index < sizeof(buffer) - 1)
							{
								buffer[buffer_index++] = ' ';
								count++;
							}
						}
					}

					break;
				}
				case 'd':
				case 'i':
				{
					int num = va_arg(args, int);
					int printed;
					if (precision != -1)
					{
						printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
								   "%*.*d", width, precision, num);
					}
					else
					{
						if (flag_zero_padding)
						{
							printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "%0*d", width, num);
						}
						else
						{
							printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "%*d", width, num);
						}
					}
					buffer_index += printed;
					count += printed;
					break;
				}
				case 'u':
				{
					unsigned int num = va_arg(args, unsigned int);
					int printed;
					if (precision != -1)
					{
						printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
								   "%*.*u", width, precision, num);
					}
					else
					{
						if (flag_zero_padding)
						{
							printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "%0*u", width, num);
						}
						else
						{
							printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "%*u", width, num);
						}
					}
					buffer_index += printed;
					count += printed;
					break;
				}
				case 'o':
				{
					unsigned int num = va_arg(args, unsigned int);
					int printed;
					if (precision != -1)
					{
						printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
								   "%*.*o", width, precision, num);
					}
					else
					{
						if (flag_zero_padding)
						{
							printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "%0*o", width, num);
						}
						else
						{
							printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "%*o", width, num);
						}
					}
					buffer_index += printed;
					count += printed;
					break;
				}
				case 'x':
				{
					unsigned int num = va_arg(args, unsigned int);
					int printed;
					if (precision != -1)
					{
						printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
								   "%*.*x", width, precision, num);
					}
					else
					{
						if (flag_zero_padding)
						{
							printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "%0*x", width, num);
						}
						else
						{
							printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "%*x", width, num);
						}
					}
					buffer_index += printed;
					count += printed;
					break;
				}
				case 'X':
				{
					unsigned int num = va_arg(args, unsigned int);
					int printed;
					if (precision != -1)
					{
						printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
								   "%*.*X", width, precision, num);
					}
					else
					{
						if (flag_zero_padding)
						{
							printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "%0*X", width, num);
						}
						else
						{
							printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "%*X", width, num);
						}
					}
					buffer_index += printed;
					count += printed;
					break;
				}
				case 'b':
				{
					unsigned int num = va_arg(args, unsigned int);
					int printed;
					if (precision != -1)
					{
						printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
								   "%*.*s", width, precision, decimal_to_binary(num));
					}
					else
					{
						printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
								   "%*s", width, decimal_to_binary(num));
					}
					buffer_index += printed;
					count += printed;
					break;
				}
				case 'S':
				{
					char *str = va_arg(args, char *);
					if (str == NULL)
						str = "(null)";

					int str_length = strlen(str);
					int available_space = sizeof(buffer) - buffer_index - 1;

					if (!flag_left_align)
					{
						/* Padding with spaces */
						if (width > str_length)
						{
							int padding = width - str_length;
							while (padding-- > 0 && buffer_index < sizeof(buffer) - 1)
							{
								buffer[buffer_index++] = ' ';
								count++;
							}
						}
					}

					for (int i = 0; i < str_length; i++)
					{
						if (str[i] > 0 && (str[i] < 32 || str[i] >= 127))
						{
							int printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
									   "\\x%02X", (unsigned char)str[i]);
							buffer_index += printed;
							count += printed;
						}
						else
						{
							buffer[buffer_index++] = str[i];
							count++;
						}
					}

					if (flag_left_align)
					{
						/* Padding with spaces */
						if (width > str_length)
						{
							int padding = width - str_length;
							while (padding-- > 0 && buffer_index < sizeof(buffer) - 1)
							{
								buffer[buffer_index++] = ' ';
								count++;
							}
						}
					}

					break;
				}
				case 'p':
				{
					void *ptr = va_arg(args, void *);
					int printed = snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index,
							   "%#lx", (unsigned long)ptr);
					buffer_index += printed;
					count += printed;
					break;
				}
				case 'r':
				{
					char *str = va_arg(args, char *);
					if (str == NULL)
						str = "(null)";

					int str_length = strlen(str);
					int available_space = sizeof(buffer) - buffer_index - 1;

					if (!flag_left_align)
					{
						/* Padding with spaces */
						if (width > str_length)
						{
							int padding = width - str_length;
							while (padding-- > 0 && buffer_index < sizeof(buffer) - 1)
							{
								buffer[buffer_index++] = ' ';
								count++;
							}
						}
					}

					for (int i = str_length - 1; i >= 0; i--)
					{
						buffer[buffer_index++] = str[i];
						count++;
					}

					if (flag_left_align)
					{
						/* Padding with spaces */
						if (width > str_length)
						{
							int padding = width - str_length;
							while (padding-- > 0 && buffer_index < sizeof(buffer) - 1)
							{
								buffer[buffer_index++] = ' ';
								count++;
							}
						}
					}

					break;
				}
				case 'R':
				{
					char *str = va_arg(args, char *);
					if (str == NULL)
						str = "(null)";

					int str_length = strlen(str);
					int available_space = sizeof(buffer) - buffer_index - 1;

					if (!flag_left_align)
					{
						/* Padding with spaces */
						if (width > str_length)
						{
							int padding = width - str_length;
							while (padding-- > 0 && buffer_index < sizeof(buffer) - 1)
							{
								buffer[buffer_index++] = ' ';
								count++;
							}
						}
					}

					for (int i = 0; i < str_length; i++)
					{
						if ((str[i] >= 'A' && str[i] <= 'M') || (str[i] >= 'a' && str[i] <= 'm'))
							buffer[buffer_index++] = str[i] + 13;
						else if ((str[i] >= 'N' && str[i] <= 'Z') || (str[i] >= 'n' && str[i] <= 'z'))
							buffer[buffer_index++] = str[i] - 13;
						else
							buffer[buffer_index++] = str[i];
						count++;
					}

					if (flag_left_align)
					{
						/* Padding with spaces */
						if (width > str_length)
						{
							int padding = width - str_length;
							while (padding-- > 0 && buffer_index < sizeof(buffer) - 1)
							{
								buffer[buffer_index++] = ' ';
								count++;
							}
						}
					}

					break;
					break;
				}
				default:
				{
					buffer[buffer_index++] = '%';
					buffer[buffer_index++] = *format;
					count += 2;
					break;
				}
			}

			format++;
		}
		else
		{
			buffer[buffer_index++] = *format;
			count++;
			format++;
		}

		if (buffer_index >= sizeof(buffer) - 1)
		{
			write(1, buffer, buffer_index);
			buffer_index = 0;
		}
	}

	va_end(args);

	if (buffer_index > 0)
		write(1, buffer, buffer_index);

	return count;
}

