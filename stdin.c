#include "shell.h"

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
	char *newline = NULL, *temp = NULL;
	ssize_t nread, tot_bytes = 0, line_len = 0, rem_len;

	if (lineptr == NULL || n == NULL || fd < 0)
		return (-1);
	if (*lineptr == NULL)
	{
		*n = 64;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
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
		{
			if (*temp ==  '\n')
			{
				newline = temp;
				break;
			}
		}
		if (newline)
		{
			line_len = newline - bpos + 1;
			if (*n < (unsigned int) line_len)
			{
				*lineptr = _realloc(*lineptr, line_len);
				if (*lineptr == NULL)
					return (-1);
				*n = line_len;
			}
			_strncpy(*lineptr, bpos, line_len);
			(*lineptr)[line_len - 1] = '\0';
			tot_bytes += line_len;
			bpos = newline + 1;
			break;
		}
		rem_len = bstop - bpos;
		if ((long int)(*n) < tot_bytes + rem_len)
		{
			*lineptr = _realloc(*lineptr, tot_bytes + rem_len);
			if (*lineptr == NULL)
				return (-1);
			*n = tot_bytes + rem_len;
		}
		_strncpy(*lineptr + tot_bytes, bpos, rem_len);
		tot_bytes += rem_len;
		bpos = bstop;
	}
	return (tot_bytes);
}

/**
 * sigint_handler - a handler function for the SIGINT signal
 *	(Control-C combination keys).
 * @signum: .
 */
void sigint_handler(int signum)
{
	(void)signum;
	_putchar('\n');
	_putchar('$');
	_putchar(' ');
	fflush(stdout);
}
