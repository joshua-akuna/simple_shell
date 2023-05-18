#include "shell.h"
/**
 * infinite_loop - starts an infinite loop dislaying a prompt
 *	if shell is in interactive mode.
 * @state: a struct of type shell_t that stores
 *	the current state of the shell program.
 * Return: Always 0.
 */

int infinite_loop(shell_t *state)
{
	const char *prompt = "$ ";
	size_t line_len = 0;

	while (1)
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
		if (getline(&(state->line), &line_len, stdin) == EOF)
		{
			free(state->line);
			_putchar('\n');
			break;
		}
		if ((state->line)[_strlen(state->line) - 1] == '\n')
			state->line[_strlen(state->line) - 1] = '\0';
		run_cmd(state);
		free(state->line);
		state->line = NULL;
	}
	return (0);
}
