#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);

	int printed_chars = 0;
	char current_char;

	while ((current_char = *format++))
	{
		if (current_char == '%')
		{
			current_char = *format++;

			if (current_char == 'c')
			{
				int value = va_arg(args, int);
				putchar(value);
				printed_chars++;
			}
			else if (current_char == 's')
			{
				char *value = va_arg(args, char *);
				while (*value)
				{
					putchar(*value++);
					printed_chars++;
				}
			}
			else if (current_char == '%')
			{
				putchar('%');
				printed_chars++;
			}
			else
			{
				putchar('%');
				putchar(current_char);
				printed_chars += 2;
			}
		}
		else
		{
			putchar(current_char);
			printed_chars++;
		}
	}

	va_end(args);

	return printed_chars;
}

int main(void)
{
	char character = 'A';
	char *name = "John Doe";

	int chars_printed = _printf("Character: %c\nString: %s\nPercentage: %%\n", character, name);
	printf("Number of characters printed: %d\n", chars_printed);

	return 0;
}
