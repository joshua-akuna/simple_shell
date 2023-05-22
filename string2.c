#include "shell.h"
/**
 * _strcat - concatenates 2 strings.
 * @dest: string to concatenate to;
 * @src: string to be concatenated.
 * Return: a pointer to the string to be conacatenated to.
 */
char *_strcat(char *dest, const char *src)
{
	unsigned int len = 0, i, j;
	char *str = NULL;

	if (dest == NULL)
		return (_strdup((char *)src));

	if (src == NULL)
		return (_strdup(dest));

	len = _strlen(dest) + _strlen(src);
	str = (char *)  malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);

	for (i = 0; dest[i]; i++)
		str[i] = dest[i];
	for (j = 0; src[j]; j++)
		str[i + j] = src[j];
	str[i + j] = '\0';

	return (str);
}

/**
 * _strncat - concatenates first n bytes of src to dest string..
 * @dest: string to concatenate to;
 * @src: string to be concatenated.
 * @n: maximum number of bytes to concatenate.
 * Return: a pointer to the string to be conacatenated to.
 */
char *_strncat(char *dest, char *src, const unsigned int n)
{
	unsigned int len = 0, i, j;
	char *res = NULL;

	len = _strlen(dest) + n;
	res = (char *) malloc(sizeof(char) * (len + 1));

	for (i = 0; dest[i]; i++)
		res[i] = dest[i];
	for (j = 0; src[j] && j < n; j++)
		res[i + j] = src[j];
	res[i + j] = '\0';

	return (res);
}

/**
 * _strcmp - compares the equality between two string arguments.
 * @str1: the first string argument.
 * @str2: the second string argument.
 * Return: 0 if both strings are equal
 *	a [+] int if str1 is greater than str2
 *	a {-] int if str1 is less than str1.
 */
int _strcmp(char *str1, char *str2)
{
	unsigned int i = 0;

	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] == str2[i])
		{
			i++;
			continue;
		}
		return (str1[i] - str2[i]);
	}
	return (0);
}

/**
 * _strncmp - comapares the equality between the first n bytes
 *	of two string arguments.
 * @str1: the first string argument.
 * @str2: the second string argument.
 * @n: the first n bytes.
 * Return: 0 if the first n bytes of both strings are equal
 *	a [+] int if the first n bytes of str1 is greater the str2.
 *	a [-] int if the first n bytes of str1 is less than str2.
 */
int _strncmp(const char *str1, const char *str2, const unsigned int n)
{
	unsigned int i = 0;

	for (i = 0; i < n && (str1[i] || str2[i]); i++)
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	return (0);
}

/**
 * _strncpy - copies the character contents of src to dest.
 * @dest: string to copy to.
 * @src: string to copy from.
 * @n: the number of bytes to copy.
 * Return: pointer to the dest string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	unsigned int i;

	for (i = 0; i < (unsigned int)n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < (unsigned int)n; i++)
		dest[i] = '\0';

	return (dest);
}
