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
