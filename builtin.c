#include "shell.h"

char *get_current_dir(void);
void free_all(shell_t *state);
/**
 * _cddir - changes the current working directory of the
 *	current shell execution environment.
 * @state: a struct of type shell_t that stores the current
 *	state of the running shell program.
 * Return: 0 when successful.
 */
int _cddir(shell_t *state)
{
	char *dir = state->cmds[1] ? _strdup(state->cmds[1]) : NULL;
	char *home = NULL, *nextdir = NULL, *curdir = NULL;
	struct stat st;
	char *arr[5];

	state->cmds = arr;
	curdir = get_current_dir();
	if (curdir == NULL)
		return (-1);
	/* checks if a directory operand was specified */
	if (dir == NULL || _strcmp(dir, "~") == 0)
	{
		/* if dir is NULL, get HOME environment variable */
		home = _getenv(state->envps, "HOME");
		if (home == NULL)
			return (-1);
		nextdir = home;
	}
	else
	{
		if (_strncmp(dir, "-", 1) == 0)
		{
			nextdir = _getenv(state->envps, "OLDPWD");
			nextdir = nextdir ? nextdir : curdir;
		}
		else if (_strncmp(dir, "/", 1) == 0
				|| _strncmp(dir, ".", 1) == 0
				|| _strncmp(dir, "..", 2) == 0)
			nextdir = _strdup(dir);
		else
		{
			nextdir = append_file_to_dir(curdir, dir);
			if (nextdir == NULL)
				return (-1);
		}

	}
	if (stat(nextdir, &st) != 0)
	{
		_puts("-bash: cd: dir: No such file or directory");
		free(nextdir);
		free(dir);
		free(curdir);
		return (-1);
	}
	if (S_ISDIR(st.st_mode) == 0)
	{
		_puts("-bash: cd: dir: Not a directory");
		free(nextdir);
		free(dir);
		free(curdir);
		return (-1);
	}
	if (chdir(nextdir) == 0)
	{
		_setenv(state, "OLDPWD", curdir);
		_setenv(state, "PWD", nextdir);
	}
	free(nextdir);
	free(curdir);
	free(dir);
	return (0);
}

/**
 * get_current_dir - gets the current working directory.
 * Return: the current working directory if successful
 *	else NULL.
 */
char *get_current_dir(void)
{
	char *buf = NULL;
	size_t len = 0;

	while (1)
	{
		len += 8;
		buf = _realloc(buf, len);
		if (buf == NULL)
			return (NULL);
		if (getcwd(buf, len) != NULL)
			return (buf);
		if (errno != ERANGE)
		{
			free(buf);
			return (NULL);
		}
	}
}

/**
 * exitshell - terminates the calling process.
 * @state: a shell_state struct that stores the current
 *	state of the simple shell program.
 * Return: Nothing.
 */
void exitshell(shell_t *state)
{
	int code = EXIT_SUCCESS;
	int status;

	if (state->av[1])
	{
		status = _atoi(state->av[1]);
		if (status == -1)
		{
			code = 1;
			free_all(state);
			exit(code);
		}
		code = status;
	}
	free_all(state);
	exit(code);
}


void free_all(shell_t *state)
{
	free(state->line);
	free(state->stripped_cmd);
	free_list(state->path);
	free_list(state->envps);
	free_list(state->aliases);
}
