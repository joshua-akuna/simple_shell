#include "shell.h"

/**
 * handle_alias - handles all operations related to the
 *	alias command including print all aliases, printing aliases
 *	whose keys are user arguments and adding new aliases.
 * @state: a struct shell_state that stores the current state
 *	for the shell.
 * Return: 0 if successful else -1.
 */
int handle_alias(shell_t *state)
{
	char *arg = state->cmds[1];

	if (arg)
	{
		if (_strchr(arg, '='))
			put_alias(state);
		else
			print_aliases_by_name(state);
	}
	else
		print_all_aliases(state);
	return (0);
}

/**
 * print_all_aliases - prints all the shell aliases.
 * @state: a struct shell_state that stores the current
 *	state for the shell.
 * Return: 0 if successful.
 */
int print_all_aliases(shell_t *state)
{
	record_t *head = state->aliases;
	char *str = NULL;

	while (head)
	{
		str = _strdup(head->str);
		_puts(str);
		free(str);
		head = head->next;
	}
	return (0);
}

/**
 * print_aliases_by_name - prints all the aliases
 *	whose key is equal to the names entered as arguments.
 * @state: a struct shell_state that stores the current
 *	state for the shell.
 * Return: 0 if successful else -1.
 */
int print_aliases_by_name(shell_t *state)
{
	int i = 0;
	record_t *alias_head = state->aliases;
	char *str = NULL;

	if (alias_head == NULL)
		return (0);
	while (alias_head)
	{
		str = (char *)alias_head->str;
		for (i = 1; state->cmds[i]; i++)
		{
			if (strncmp(str, state->cmds[i], _strlen(state->cmds[i])) == 0
				&& str[_strlen(state->cmds[i])] == '=')
				_puts(str);
		}
		alias_head = alias_head->next;
	}
	return (0);
}

/**
 * put_alias - adds a new alias to the list of aliases o
 *	updates an existing alias if the name of the alias
 *	to be added already exists.
 * @state: a struct shell_state that stores the current
 *	state for the shell.
 * Return: 0 if successful else -1.
 */
int put_alias(shell_t *state)
{
	char *key = NULL, *value = NULL;
	char *new_alias = NULL;
	char *line = _strdup(state->line);
	char *args[16];
	int i = 0;

	(void)new_alias;
	args[i] = _strtok(line, " ");
	while (args[i++] != NULL)
		args[i] = _strtok(NULL, "=\'\"");

	for (i = 1; args[i]; i++)
	{
		key = args[i++];
		value = args[i];
		new_alias = create_alias_line(key, value);
		add_node_to_tail(&(state->aliases), new_alias);
		free(new_alias);
		new_alias = NULL;
	}
	free(line);
	return (0);
}
