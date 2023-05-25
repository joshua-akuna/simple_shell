#include "shell.h"

/**
 * init_envp_list - creates a linked list from the for the
 *	shell environment variable.
 * @envps: a pointer the head of a linked list of type record_t.
 * Return: 0 if successful else -1;
 */
int init_envp_list(record_t **envps)
{
	int i;

	if (envps == NULL)
		return (-1);

	for (i = 0; environ[i]; i++)
		add_node_to_tail(envps, environ[i]);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable.
 * @envps: a linked list of the environment variables.
 * @key: the environment variable to get.
 * Return: a pointer to the environment variable if successful
 *	else NULL.
 */
char *_getenv(record_t *envps, const char *key)
{
	record_t *node = NULL;
	char *str = NULL, *val;
	size_t len = 0;

	if (envps == NULL)
		return (NULL);
	node = envps;
	len = _strlen(key);

	while (node)
	{
		str = (char *)node->str;
		if (strncmp(str, key, len) == 0 && str[len] == '=')
		{
			val = strchr(str, '=');
			val++;
			return (_strdup(val));
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * printenv - prints a linkedlist of the environment variables
 * @state: a struct of type shell_t that stores the
 *	current state of the shell.
 * Return: Always 0.
 */
int printenv(shell_t *state)
{
	print_list(state->envps);
	return (0);
}

/**
 * _setenv - changes or add an environment variable.
 * @state: a struct of type shell_t that stores the current
 *	state of the shell.
 * @new_name: name of the environment variable to add.
 * @new_value: a new value for the environment variable @name
 * Return: 0 on success or -1 on error.
 */
int _setenv(shell_t *state, char *new_name, char *new_value)
{
	record_t *envlist = state->envps;
	char *name = new_name;
	char *value = new_value;
	const char *var = NULL, *sep = "=";
	char *str = NULL;
	int overwrite = 0;

	(void)overwrite;
	if (name == NULL || _strlen(name) == 0 || _strchr(name, '='))
		return (-1);

	var = append_value_to_name(name, value, sep);
	if (var == NULL)
		return (-1);

	while (envlist)
	{
		str = (char *)envlist->str;
		if (strncmp(str, name, _strlen(name)) == 0
				&& str[_strlen(name)] == '=')
		{
			free(str);
			envlist->str = (char *)var;
			return (0);
		}
		envlist = envlist->next;
	}
	add_node_to_tail(&(state->envps), var);
	return (0);
}

/**
 * _unsetenv - deletes a variable name and its value from
 *	the environment.
 * @state: a struct of type shell_t that stores the current
 *	state of the shell.
 * Return: 0 if successful else -1.
 */
int _unsetenv(shell_t *state)
{
	record_t *node = state->envps;
	char *name = state->cmds[1] ? state->cmds[1] : NULL;
	char *str = NULL;

	if (name == NULL || _strlen(name) == 0 || _strchr(name, '='))
		return (-1);

	while (node)
	{
		str = (char *)node->str;
		if (strncmp(str, name, _strlen(name)) == 0
				&& str[_strlen(name)] == '=')
		{
			return (delete_node_by_id(&(state->envps), node->id));
		}
		node = node->next;
	}
	return (0);
}
