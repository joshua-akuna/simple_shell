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
	char *temp = NULL, *res = NULL;

	temp = _strcat(name, sep);
	if (temp == NULL)
		return (NULL);
	
	res = _strcat(temp, value);
	free(temp);

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
	char *alias, *temp, *val;

	name = _strtok(name, " ");
	value = _strtok(value, " ");

	temp = _strcat("\'", value);
	val = _strcat(temp, "\'");
	free(temp);
	temp = NULL;
	temp = _strcat(name, "=");
	alias = _strcat(temp, val);
	free(temp);
	free(val);

	return (alias);
}

/**
 * _atoi - converts a string to an integer.
 * @str: a char pointer to a string.
 * Return: an integer value of str.
 */
int _atoi(char *str)
{
	unsigned int res, i, sign, end;

	res = 0;
	end = 0;
	sign = 1;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == 45)
			sign *= -1;

		while (str[i] >= '0' && str[i] <= '9')
		{
			end = 1;
			res = res * 10 + str[i] - '0';
			i++;
		}
		if (end)
			break;
	}
	return (res * sign);
}

/**
 * _itoa - converts a integer to a string.
 * @num: an integer to be converted.
 * Return: the string version of n.
 */
char *_itoa(int num)
{
	char *str = NULL, rem;
	int num1 = num, num2 = num, len = 0, i;

	while (num1 != 0)
	{
		len++;
		num1 /= 10;
	}

	if (num == 0)
		len = 1;

	str = (char *) malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);

	i = len - 1;
	if (num2 < 0)
	{
		str[0] = '-';
		num2 = -num2;
		i++;
	}

	while (num2 != 0)
	{
		rem = num2 % 10;
		str[i] = '0' + rem;
		num2 /= 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}
