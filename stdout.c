#include "shell.h"
/**
 * _putchar - prints a single character.
 * @c: the character to print.
 * Return: Always 1, number of characters printed.
 */
int _putchar(const char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * _puts - prints a line of text with a newline appended to it.
 * @str: a line of text to print.
 * Return: the number of characters printed minus the null byte.
 */
int _puts(const char *str)
{
	int nwrite;

	if (str == NULL)
		return (-1);

	for (nwrite = 0; str[nwrite]; nwrite++)
		_putchar(str[nwrite]);
	_putchar('\n');
	nwrite++;
	return (nwrite);
}

/**
 * printerr - a variable argument function that prints an error
 *	message to the standard error.
 * @format: a string that defines the format for the string arguments
 *	to be printed.
 * Return: Nothing.
 */
void printerr(char *format, ...)
{
	va_list valist;
	int num;
	char *n;
	char c;
	char *str;

	va_start(valist, fmt);

	while (*fmt)
		switch (*fmt++)
		{
			case 's':
				str = va_arg(valist, char *);
				write(STDERR_FILENO, str, _strlen(str));
				break;
			case 'd':
				num = va_arg(valist, int);
				n = _itoa(num);
				write(STDERR_FILENO, &n, _strlen(n));
				break;
			case 'c':
				c = (char) va_arg(valist, int);
				write(STDERR_FILENO, &c, 1);
				break;
		}
	va_end(valist);
}
