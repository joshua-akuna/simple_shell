#include "shell.h"

/**
 * init_path_list - create a linked list from the
 * @head: a double pointer to a string of record_t struct.
 * @envp: a string of variables.
 * Return: a pointer to the head of the linked list.
 */
record_t *init_path_list(record_t **head, const char *envp)
{
	char *value = strdup(envp);
	char *token = NULL;

	if (head == NULL)
		return (NULL);

	token = strtok(value, ":");
	while (token)
	{
		add_node_to_tail(head, token);
		token = strtok(NULL, ":");
	}
	free(value);
	return (*head);
}

/**
 * init_pathvp - gets the PATH variable and converts it to
 *	a linked list.
 * @pathenv: a double pointer to the head of the linked list.
 * @env: the environment variable.
 * Return: 0 if successful else -1.
 */
int init_pathvp(record_t **pathenv, record_t *env)
{
	char *key = "PATH";
	char *pathvp = _getenv(env, key);

	if (pathvp)
	{
		init_path_list(pathenv, pathvp);
		free(pathvp);
		return (0);
	}
	return (-1);
}
