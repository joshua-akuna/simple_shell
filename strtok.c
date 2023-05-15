#include "shell.h"
/**
 * tokenize - splits a string into tokens along delimiters.
 * @tokens: an array to store the tokens.
 * @str: the string argument to split into tokens.
 * @delim: the delimiters along which a string is to be split.
 * Return: number of tokens.
 */
int tokenize(char *tokens[], char *str, const char *delim)
{
	int ntok = 0;

	tokens[ntok] = strtok(str, delim);
	while (tokens[ntok++] != NULL)
	{
		tokens[ntok] = strtok(NULL, delim);
	}
	tokens[ntok] = NULL;

	return (ntok);
}
