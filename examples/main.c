#include "shell.h"

int main(void)
{
	char *str = "ls -l #prints a list", *delim = "#";
	char *token[16];
	int i = 0;

	str = strdup(str);
	token[i] = _strtok(str, delim);
	while (token[i++])
		token[i] = _strtok(NULL, delim);

	for (i = 0; token[i]; i++)
		printf("%s\n", token[i]);
	free(str);

	return (0);
}
