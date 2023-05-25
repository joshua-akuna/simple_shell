#include "shell.h"

/**
 * _strdup - returns a pointer to a newly allocated space
 *	in memory, which contains a copy of the string argument.
 * @src: a pointer to the string argument.
 * Return: a pointer to the allocated memory
 *	else NULL if malloc fails.
 */
char *_strdup(const char *src)
{
	char *dest = NULL;
	unsigned int  len = 0;

	/* checks that the string argument is valid */
	if (src == NULL)
		return (NULL);
	/* gets the length of the string argument */
	len = _strlen(src);
	/* allocate a memory space of len and a null byte */
	dest = (char *) malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	/* copies the content of the src to the dest */
	_strncpy(dest, (char *)src, len);
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

/**
 * _strstr - finds the first occurence of "needle" in "haystack".
 * @haystack: a string in which the "needle" is scanned for.
 * @needle: a string whose index pointer is to be scanned for
 *	in "haystack".
 * Return: a pointer to the first occurrence of "needle" if found
 *	else NULL.
 */
char *_strstr(char *haystack, char *needle)
{
	unsigned int i, j, found;

	if (haystack == NULL)
		return (NULL);

	if (needle == NULL || *needle == '\0')
		return (haystack);

	(void)found;
	for (i = 0; haystack[i]; i++)
	{
		found = 1;
		j = 0;

		if (haystack[i] == needle[j])
		{
			for (; needle[j]; j++)
			{
				if (needle[j] != haystack[i + j])
				{
					found = 0;
					break;
				}
			}
			if (found)
				return (haystack + i);
		}
	}
	return (NULL);
}

/**
 * _strpbrk - finds the first occurence of a byte in "search"
 *	that matches any byte in the "accept".
 * @search: a string whose bytes is to be searched.
 * @accept: a string whose byte is to be searched for in "search".
 * Return: a pointer to the byte in "search" that mathces any byte
 *	in "accept".
 */
char *_strpbrk(char *search, const char *accept)
{
	unsigned int i = 0, j = 0, found;

	while (search[i] != '\0')
	{
		found = 0;
		j = 0;
		while (accept[j] != '\0')
		{
			if (search[i] == accept[j])
			{
				found = 1;
				break;
			}
			j++;
		}
		if (found)
			return (search + i);
		i++;
	}
	return (NULL);
}
