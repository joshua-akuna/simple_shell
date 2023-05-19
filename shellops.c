#include "shell.h"
int sub_variables(shell_t *state);
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
		/*sub_variables(state);*/
		run_cmd(state);
		free(state->line);
		state->line = NULL;
	}
	return (0);
}

/**
 * sub_variables - TODO:
 * @state: a struct shell_state that stores the current state
 *	of the simple shell program.
 * Return: 0 if variable substitution was success or no
 *	varaibles to substitute else return -1.
 */
int sub_variables(shell_t *state)
{
	char *line = _strdup(state->line);
	char *sub_line = NULL, *env = NULL;
	char *cmds[16];
	int i;
	char *res = NULL;

	(void)sub_line;
	(void)env;
	tokenize(cmds, line, " ");
	for (i = 0; cmds[i]; i++)
	{
		if (_strncmp(cmds[i], "$", 1) == 0 && cmds[i][1])
		{
			if (_strncmp("$?", cmds[i], _strlen(cmds[i])) == 0)
			{
				res = _itoa(12);
				_puts(res);
			}
			else if (_strncmp("$$", cmds[i], _strlen(cmds[i])) == 0)	
			{
				res = _itoa(getpid());
				_puts(res);
			}
			else
			{
				res = _strstr(cmds[i], "$");
				res = _getenv(state->envps, res + 1);
				if (res == NULL)
					res = _strdup(" ");
				_puts(res);
			}
		}
		else
			_puts(cmds[i]);
		free(res);
	}
	free(line);

	return (0);
}
