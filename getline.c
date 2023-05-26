#include "shell.h"

int copyline(char **lineptr, size_t *n, ssize_t *tot_bytes,
		ssize_t *rem_len, char *bpos, char *bstop);
/**
 * _getline - my custom implementation of the
 *	getline function.
 * @lineptr: a string buffer which used to store
 *	get user input.
 * @n: number of characters in the lineptr buffer.
 * @fd: a file descriptor to the file to read from..
 * Return: the number of characters read from the user.
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUF_SIZE];
	static char *bpos = buffer, *bstop = buffer;
	char *newline = NULL, *temp;
	ssize_t nread, tot_bytes = 0, line_len = 0, rem_len;

	if (validate_line_param(lineptr, n, fd) == -1)
		return (-1);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		if (bpos == bstop)
		{
			nread = read(fd, buffer, BUF_SIZE);
			if (nread <= 0)
			{
				if (tot_bytes == 0)
					return (-1);
				break;
			}
			bpos = buffer;
			bstop = buffer + nread;
		}
		for (temp = bpos; temp < bstop; temp++)
			if (*temp == '\n')
			{
				newline = temp;
				break;
			}
		if (newline)
		{
			line_len = newline - bpos + 1;
			if (realloc_line(lineptr, n, line_len) == -1)
				return (-1);
			_strncpy(*lineptr, bpos, line_len);
			(*lineptr)[line_len - 1] = '\0';
			tot_bytes += line_len;
			bpos = newline + 1;
			break;
		}
		rem_len = bstop - bpos;
		if (copyline(lineptr, n, &tot_bytes, &rem_len, bpos, bstop) == -1)
			return (-1);
	}
	return (tot_bytes);
}


int copyline(char **lineptr, size_t *n, ssize_t *tot_bytes,
		ssize_t *rem_len, char *bpos, char *bstop)
{
	if ((long int)(*n) < *tot_bytes + *rem_len)
	{
		*lineptr = _realloc(*lineptr, *tot_bytes + *rem_len);
		if (lineptr == NULL)
			return (-1);
		*n = *tot_bytes + *rem_len;
	}
	_strncpy(*lineptr + *tot_bytes, bpos, *rem_len);
	*tot_bytes += *rem_len;
	*bpos = *bstop;
	return (0);
}

/**
 * validate_line_param - validates the input parameters
 *	for the _getline function.
 * @lineptr: a string buffer which used to store
 *	get user input.
 * @n: number of characters in the lineptr buffer.
 * @fd: a file descriptor to the file to read from..
 * Return: 0 if input is valid else -1..
 */
int validate_line_param(char **lineptr, size_t *n, int fd)
{
	if (lineptr == NULL || n == NULL || fd < 0)
		return (-1);
	if (*lineptr == NULL)
	{
		*n = 64;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	return (0);
}

/**
 * realloc_line - reallocates the buffer if it is full.
 * @lineptr: a string buffer which used to store
 *	get user input.
 * @n: number of characters in the lineptr buffer.
 * @line_len: a file descriptor to the file to read from..
 * Return: return 0 if successful else -1..
 */
int realloc_line(char **lineptr, size_t *n, size_t line_len)
{
	if (*n < (unsigned int)line_len)
	{
		*lineptr = _realloc(*lineptr, line_len);
		if (*lineptr == NULL)
			return (-1);
		*n = line_len;
	}
	return (0);
}
