#include "shell.h"

/**
 * main - test for _strtok function and comments.
 * Return: Always 0.
 */
int main(void)
{
	char *cmds[] = {
		"echo $$ # la -la",
		NULL,
	};
	int i;
	char *res;

	(void)i;
	/*
	for (i = 0; cmds[i]; i++)
	{
		if (str == NULL)
			return (-1);

		_puts(str);
		str = _strtok(str, "#");
		_puts(str);
	}
	*/
	res = _strstr(cmds[0], "pa");
	res = res ? res : "nil";
	_puts(res);
	res = _strstr(cmds[0], "$$ #");
	res = res ? res : "nil";
	_puts(res);
	res = _strstr(cmds[0], "$$#");
	res = res ? res : "nil";
	_puts(res);
	return (0);
}
