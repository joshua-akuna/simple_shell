#include "shell.h"

int validate_input(char *line, char *name);
/**
 * interactive_loop - starts an infinite loop dislaying a prompt
 *	if shell is in interactive mode.
 * @state: a struct of type shell_t that stores
 *	the current state of the shell program.
 * Return: Always 0.
 */
int interactive_loop(shell_t *state)
{
	const char *prompt = "$ ";
	size_t line_len = 0;
	char *cmds[16];
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, _strlen(prompt));
		if (_getline(&(state->line), &line_len, STDIN_FILENO) == EOF)
		{
			free(state->line);
			if (isatty(STDIN_FILENO))
				_putchar('\n');
			break;
		}
		if ((state->line)[_strlen(state->line) - 1] == '\n')
			state->line[_strlen(state->line) - 1] = '\0';
		if (isatty(STDIN_FILENO))
		{
			state->cmd = state->line;
			semi_colon_handler(state);
		}
		else
		{
			tokenize(cmds, state->line, " \t\n");
			for (i = 0; cmds[i]; i++)
			{
				state->cmd = cmds[i];
				semi_colon_handler(state);
			}
		}
		free(state->line);
		state->line = NULL;
	}
	return (state->status_code);
}

/**
 * non_interactive - execute the input commands in non-interactive
 *	mode.
 * @state: a struct of type shell_state that stores the current
 *	state of the shell program.
 * Return: the current status of the simple shell program.
 */
int non_interactive(shell_t *state)
{
	size_t len = 0;

	while (_getline(&(state->line), &len, state->fd) > 0)
	{
		if ((state->line)[_strlen(state->line) - 1] == '\n')
			state->line[_strlen(state->line) - 1] = '\0';
		semi_colon_handler(state);
		free(state->line);
		state->line = NULL;
	}
	return (state->status_code);
}

/**
 * validate_input - checks if the user command starts
 *	with valid characters.
 * @line: user input line.
 * @name: the first argument of argv array.
 * Return: 0 if userinput is valid else -1.
 */
int validate_input(char *line, char *name)
{
	if (*line == ';' && *(line + 1) == ';')
	{
		printerr(name);
		printerr(": syntax error near unexpected token ';;'\n");
		return (-1);
	}
	else if (*line == ';')
	{
		printerr(name);
		printerr(": syntax error near unexpected token ';'\n");
		return (-1);
	}
	else if (*line == '&' && *(line + 1) == '&')
	{
		printerr(name);
		printerr(": syntax error near unexpected token '&&'\n");
		return (-1);
	}
	else if (*line == '&')
	{
		printerr(name);
		printerr(": syntax error near unexpected token '&'\n");
		return (-1);
	}
	else if (*line == '|' && *(line + 1) == '|')
	{
		printerr(name);
		printerr(": syntax error near unexpected token '||'\n");
		return (-1);
	}
	else if (*line == '|')
	{
		printerr(name);
		printerr(": syntax error near unexpected token '|'\n");
		return (-1);
	}
	return (0);
}
