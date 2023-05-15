#include "shell.h"

/**
 * _strdup - returns a pointer to a newly allocated space
 *	in memory, which contains a copy of the string argument.
 * @src: a pointer to the string argument.
 * Return: a pointer to the allocated memory
 *	else NULL if malloc fails.
 */
char *_strdup(char *src)
{
	char *dest = NULL;
	unsigned int  len = 0;

	/* checks that the string argument is valid */
	if (src == NULL || src[0] == '\0')
		return (NULL);
	/* gets the length of the string argument */
	len = _strlen(src);
	/* allocate a memory space of len and a null byte */
	dest = malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	/* copies the content of the src to the dest */
	_memcpy(dest, src, len);
	/* add a terminating null byte at the end of the dest */
	dest[len] = '\0';

	return (dest);
}

/**
 * _memcpy - copies n bytes from src to dest.
 * @dest: memory area to copy to.
 * @src: memory area to copy from.
 * @n: number of bytes to copy.
 * Return: pointer to dest.
 */
char *_memcpy(void *dest, const void *src, size_t n)
{
	char *ptr = dest;
	char *str = (char *)src;

	while (n--)
		*ptr++ = *str++;

	return (dest);
}

/**
 * _strchr - determines a pointer to the first occurence of a
 *	character argument.
 * @str: a string argument.
 * @c: a character argument.
 * Return: a pointer to the first occurence of c argument.
 *	or NULL if c does not exist.
 */
char *_strchr(char *str, const char c)
{
	unsigned int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}

	if (str[i] == c)
		return (str + i);

	return (NULL);
}
