#include "shell.h"
/**
 * _line - my custom implementation of the
 *	getline function.
 * @lineptr: a string buffer which used to store
 *	get user input.
 * @n: number of characters in the lineptr buffer.
 * @fd: a file descriptor to the file to read from..
 * Return: the number of characters read from the user.
 */
ssize_t _line(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUF_SIZE];
	static char *bpos = buffer, *bstop = buffer;
	char *newline = NULL, *temp = NULL;
	ssize_t nread, tot_bytes = 0;
	ssize_t line_len = 0, rem_len;

	if (lineptr == NULL || n == NULL || fd < 0)
		return (-1);

	if (*lineptr == NULL)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (bpos == bstop)
		{
			nread = read(fd, buffer, BUF_SIZE);
			if(nread <= 0)
			{
				if (tot_bytes == 0)
				{
					/* No more data to read */
					printf("reads: %ld\n", nread);
					printf("EOF\n");
					return (-1);
				}
				else
					/* return partial byteread */
					break;
			}
			bpos = buffer;
			bstop = buffer + nread;
		}

		/* searches for a newline character */
		for (temp = bpos; temp < bstop; temp++)
		{
			if (*temp ==  '\n')
			{
				newline = temp;
				break;
			}
		}

		/* returns a newline if found */
		if (newline)
		{
			line_len = newline - bpos + 1;
			if (*n < (unsigned) line_len)
			{
				*lineptr = realloc(*lineptr, line_len);
				if (*lineptr == NULL)
					return (-1);
				*n = line_len;
			}
			strncpy(*lineptr, bpos, line_len);
			(*lineptr)[line_len - 1] = '\0';
			tot_bytes += line_len;
			bpos = newline + 1;
			break;
		}

		/* If we didn't find a new line character */
		/* copy the remaining buffer to the output */
		rem_len = bstop - bpos;
		if ((long int)(*n) < tot_bytes + rem_len)
		{
			*lineptr = realloc(*lineptr, tot_bytes + rem_len);
			if (*lineptr == NULL)
				return (-1);
			*n = tot_bytes + rem_len;
		}
		strncpy(*lineptr + tot_bytes, bpos, rem_len);
		tot_bytes += rem_len;
		bpos = bstop;

	}
	return (tot_bytes);
}
