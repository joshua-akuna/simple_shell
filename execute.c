#include "shell.h"
/**
 * run_cmd - finds the path to the executive program command
 *	and executes it.
 * @state: a shell_t struct that stores the current state of the shell.
 * Return: status of the executed command if successful
 *	else 127 if executable program not found.
 */
int run_cmd(shell_t *state)
{
	char *args[16];
	int status = 0;

	tokenize(args, state->line, " \t\n");
	state->cmds = args;

	if (_strcmp(state->cmds[0], "cd") == 0)
		_cddir(state);
	else if (_strcmp(state->cmds[0], "env") == 0)
		printenv(state);
	else if (_strcmp(state->cmds[0], "setenv") == 0)
		_setenv(state, state->cmds[1], state->cmds[2]);
	else if (_strcmp(state->cmds[0], "unsetenv") == 0)
		_unsetenv(state);
	else
	{
		/*_puts("no match");*/
		state->cmd_path = is_sys_cmd(args[0], state->path);
		if (state->cmd_path == NULL)
		{
			/* TODO: write a function to print errors.*/
			dprintf(STDERR_FILENO, "%s: command not found\n", args[0]);
			return (127);
		}
		status = execute(state);
		free(state->cmd_path);
	}
	return (status);
}

/**
 * execute - executes the command program on a new
 *	child thread.
 * @state: a shell_t struct that stores the current state of the shell.
 * Return: status_code.
 */
int execute(shell_t *state)
{
	pid_t cpid, tcpid;
	int wstatus = 0, status_code, err;

	cpid = fork();
	if (cpid == -1) /* checks if the fork call is successful */
	{
		perror("Error:");
		return (1);
	}

	if (cpid == 0) /* executes for the child process */
	{
		/* executing the program file*/
		err = execve(state->cmd_path, state->cmds, environ);
		/* could not find the program file to execute */
		if (err == -1)
		{
			perror("execve");
			return (2);
		}
	}
	else /* executes for the parent process */
	{
		/* parent process waits for its child to terminate. */
		tcpid = wait(&wstatus);
		if (tcpid == -1)
		{
			perror("wait");
			return (2);
		}
		if (WIFEXITED(wstatus))
			status_code = WEXITSTATUS(wstatus);
	}
	return (status_code);
}

/**
 * is_sys_cmd - finds the command program in the PATH variable.
 * @cmd: a user input string to a program file.
 * @pathenv: a fresh copy of an array of strings for the PATH variable.
 * Return: an absolute path to the command program if command found
 *	else NULL.
 */
char *is_sys_cmd(char *cmd, record_t *pathenv)
{
	record_t *pathvp = pathenv;
	char *absolute_path = NULL, *token = NULL;
	struct stat st;

	if (stat(cmd, &st) == 0)
		return (cmd);

	while (pathvp)
	{
		token = (char *)pathvp->str;
		absolute_path = append_file_to_dir(cmd, token);
		if (stat(absolute_path, &st) == 0
				&& st.st_mode & S_IXUSR)
			return (absolute_path);
		free(absolute_path);
		pathvp = pathvp->next;
	}
	return (NULL);
}

/**
 * append_file_to_dir - create an absolute path by appending
 *	a file to a directory path.
 * @file: file to append.
 * @dir: dir path to append file to.
 * Return: the absolute path of the file appended to the
 *	directory path.
 */
char *append_file_to_dir(char *file, char *dir)
{
	char *sep = "/";
	int len;
	char *path = NULL;

	path = _strdup(dir);
	len = _strlen(file) + _strlen(path) + 1;
	path = _realloc(path, len + 1);
	_strcat(path, sep);
	_strcat(path, file);
	path[len] = '\0';

	return (path);
}
