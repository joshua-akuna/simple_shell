#include "shell.h"
/**
 * append_value_to_name - appends the value argument to the
 *	name argument separated by the separator argument.
 * @name: a string agument.
 * @value: a string argument.
 * @sep: a string argument that represents the separator
 *	between the name and value..
 * Return: a pointer to the concatenated new string
 */
char *append_value_to_name(char *name, char *value, const char *sep)
{
	int len;
	char *res = NULL;

	res = _strdup(name);
	if (res == NULL)
		return (NULL);

	len = _strlen(name) + _strlen(value) + _strlen(sep);
	res = _realloc(res, len + 1);
	if (res == NULL)
		return (NULL);

	if (sep != NULL)
		_strcat(res, sep);
	if (value != NULL)
		_strcat(res, value);

	res[len] = '\0';

	return (res);
}

/**
 * create_alias_line - creates a new alias from the alias
 *	name and value.
 * @name: a string for the alias name.
 * @value: a string for the alias value.
 * Return: a string of the newly created alias line or NULL
 */
char *create_alias_line(char *name, char *value)
{
	int len;
	char *alias;

	name = _strtok(name, " ");
	value = _strtok(value, " ");
	alias = _strdup(name);
	if (alias == NULL)
		return (NULL);

	len = _strlen(name) + _strlen(value) + 3;

	alias = _realloc(alias, len + 1);
	if (alias == NULL)
		return (NULL);

	_strcat(alias, "=");
	_strcat(alias, "'");
	_strcat(alias, value);
	_strcat(alias, "'");
	alias[len] = '\0';

	return (alias);
}
