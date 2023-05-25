#include "shell.h"
int isvalidcmd(char *cmd);
/**
 * run_cmd - finds the path to the executive program command
 *	and executes it.
 * @state: a shell_t struct that stores the current state of the shell.
 * Return: status of the executed command if successful
 *	else 127 if executable program not found.
 */
int run_cmd(shell_t *state)
{
	char *args[32];
	int status = 0, i = 0;
	/* cloning line for this file */
	char *line = state->stripped_cmd;

	tokenize(args, line, " \t\n");
	state->cmds = args;

	if (_strcmp(state->cmds[0], "cd") == 0)
		_cddir(state);
	else if (_strcmp(state->cmds[0], "env") == 0)
		printenv(state);
	else if (_strcmp(state->cmds[0], "setenv") == 0)
		_setenv(state, state->cmds[1], state->cmds[2]);
	else if (_strcmp(state->cmds[0], "unsetenv") == 0)
		_unsetenv(state);
	else if (_strcmp(state->cmds[0], "alias") == 0)
		handle_alias(state);
	else if (_strcmp(state->cmds[0], "exit") == 0)
		exitshell(state);
	else
	{
		state->cmd_path = is_sys_cmd(args[0], state->path, state->av[0]);
		if (state->cmd_path == NULL)
			return (127);
		for (i = 0; state->cmds[i]; i++)
			state->cmds[i] = substitution_handler(state, state->cmds[i]);
		status = execute(state);
		for (i = 0; state->cmds[i]; i++)
			free(state->cmds[i]);
		free(state->cmd_path);
	}
	/* freeing line for this file */
	/*free(line);*/
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
	int wstatus;
	int i;

	for (i = 0; state->cmds[i]; i++)
		_puts(state->cmds[i]);

	cpid = fork();
	if (cpid == -1) /* checks if the fork call is successful */
	{
		perror("error:");
		return (1);
	}
	if (cpid == 0) /* executes for the child process */
	{
		/* executing the program file*/
		if (execve(state->cmd_path, state->cmds, environ) == -1)
		{
			/* could not find the program file to execute */
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
		{
			state->status_code = WEXITSTATUS(wstatus);
			if (state->status_code == 126)
			{
				printerr(_itoa(2));
				printerr("Illegal number: ");
				printerr("\n");
			}
		}
	}
	return (state->status_code);
}

/**
 * is_sys_cmd - finds the command program in the PATH variable.
 * @cmd: a user input string to a program file.
 * @pathenv: a fresh copy of an array of strings for the PATH variable.
 * @name: the first argument of the argv array.
 * Return: an absolute path to the command program if command found
 *	else NULL.
 */
char *is_sys_cmd(char *cmd, record_t *pathenv, char *name)
{
	record_t *pathvp = pathenv;
	char *absolute_path = NULL, *dir = NULL;
	int res;

	res = isvalidcmd(cmd);
	if (res == 0)
		return (_strdup(cmd));

	while (pathvp != NULL)
	{
		dir = (char *)pathvp->str;
		absolute_path = append_file_to_dir(dir, cmd);
		res = isvalidcmd(absolute_path);
		if (res == 0)
			return (absolute_path);
		free(absolute_path);
		pathvp = pathvp->next;
	}
	if (res == -1)
	{
		printerr(name);
		printerr(": 1: ");
		printerr(cmd);
		printerr(": not found\n");
	}
	else if (res == -2)
	{
		printerr(name);
		printerr(": 1: ");
		printerr(cmd);
		printerr(": permission denied\n");
	}
	else if (res == -3)
	{
		printerr(name);
		printerr(": 1: ");
		printerr(cmd);
		printerr(": Is a directory\n");
	}
	return (NULL);
}

/**
 * isvalidcmd - checks if the user command is a valid executable program.
 * @cmd: the user command to validate.
 * Return: 0 if command is a valid executable program else -1
 */
int isvalidcmd(char *cmd)
{
	struct stat st;

	if (stat(cmd, &st) == 0
			&& S_ISREG(st.st_mode)
			&& st.st_mode & S_IXUSR)
		return (0);
	else if (stat(cmd, &st) == 0
			&& S_ISREG(st.st_mode)
			&& !(st.st_mode & S_IXUSR))
		return (-2);
	else if (stat(cmd, &st) == 0
			&& S_ISDIR(st.st_mode))
		return (-3);
	return (-1);
}

/**
 * append_file_to_dir - create an absolute path by appending
 *	a file to a directory path.
 * @file: file to append.
 * @dir: dir path to append file to.
 * Return: the absolute path of the file appended to the
 *	directory path.
 */
char *append_file_to_dir(char *dir, char *file)
{
	char *sep = "/";
	char *res = NULL;
	char *abs_path = NULL;

	res = _strcat(dir, sep);
	abs_path = _strcat(res, file);
	free(res);

	return (abs_path);
}
