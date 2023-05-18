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

	tokens[ntok] = _strtok(str, delim);
	while (tokens[ntok++] != NULL)
	{
		tokens[ntok] = _strtok(NULL, delim);
	}
	tokens[ntok] = NULL;

	return (ntok);
}

/**
 * _strtok - breaks a string into a sequence of 0 or more nonempty
 *	tokens.
 * @str: a string argument to be tokenized.
 * @delim: a string argument which specifies a set of bytes that
 *	delimits the tokens in the parsed string.
 * Return: a pointer to the next token or NULL if there are no
 *	more tokens.
 */
char *_strtok(char *str, const char *delim)
{
	static char *buf;
	char *token = NULL, *token_to = NULL, *ptr = NULL;

	/* assigns "str" argument "buf" if "str" is not NULL */
	if (str != NULL)
		buf = str;
	/* returns NULL if both "str" and "buf" is NULL */
	if (buf == NULL || *buf == '\0')
		return (NULL);
	/* assigns the "delim" string to "ptr" */
	ptr = (char *)delim;
	/* move the pointer "buf" past any initial char found in delim */
	while (*buf && _strchr(ptr, *buf))
		buf++;
	/* assigns the first pointer to a non-delim char to "token_from" */
	token = buf;
	/* finds the next delim char pointer in buf */
	token_to = _strpbrk(buf, ptr);
	/* if theres a next delim pointer, assign it a null byte */
	if (token_to != NULL)
	{
		*token_to = '\0';
		token_to++;
		buf = token_to;
	}
	else /* else move the buf pointer to its last character */
		buf += _strlen(buf);
	/* return the pointer to the token */
	return (token);
}
