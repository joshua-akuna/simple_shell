#include "shell.h"

void fill_logic_array(char *cmds[], char *line);
int run_by_logic(shell_t *state);

/**
 * semi_colon_handler - splits the line entered by the user using
 *	";" delimiters and executes each token.
 * @state: a struct shell_state variable that stores the
 *	initial state of the shell program.
 * Return: Nothing.
 */
void semi_colon_handler(shell_t *state)
{
	char *line = state->cmd;
	char *semi_colon_cmds[32];
	int i;

	tokenize(semi_colon_cmds, line, ";");
	for (i = 0; semi_colon_cmds[i]; i++)
	{
		state->sc_line = semi_colon_cmds[i];
		/*run_cmd(state);*/
		split_by_logic(state);
		/*_puts(state->sc_line);*/
		state->and_op = 0;
		state->or_op = 0;
	}
	/*free(line);*/
}

/**
 * split_by_logic - splits commands command && or ||
 *	operators into an array inclusive of the && and ||
 *	operators in the order which they appear.
 * @state: a struct of type shell_state that stores the current
 *	state of the shell program.
 * Return: the status of the operation.
 */
int split_by_logic(shell_t *state)
{
	char *cmds[32];
	char *line = _strdup(state->sc_line);
	/*char *line = state->sc_line;*/

	fill_logic_array(cmds, line);
	state->logic_cmds = cmds;
	logic_handler(state);
	free(line);
	return (0);
}

/**
 * fill_logic_array - splits the logic statement into tokens using
 *	the "&|" delimiters and store them in an array.
 * @cmds: the array where the tokens are to be stored.
 * @line: a string with at least 0 logical operators to split into tokens.
 */
void fill_logic_array(char *cmds[], char *line)
{
	int i = 0, j = 0, first_cmd = 1;

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '&' && line[i + 1] == '&')
		{
			line[i++] = ' ';
			if (first_cmd)
			{
				cmds[j++] = _strtok(line, "&&");
				first_cmd = 0;
			}
			else
				cmds[j++] = _strtok(NULL, "&&");
			cmds[j++] = "&&";
		}
		else if (line[i] == '|' && line[i + 1] == '|')
		{
			line[i++] = ' ';
			if (first_cmd)
			{
				cmds[j++] = _strtok(line, "||");
				first_cmd = 0;
			}
			else
				cmds[j++] = _strtok(NULL, "||");
			cmds[j++] = "||";
		}
		else if (line[i + 1] == '\0')
		{
			if (first_cmd)
			{
				cmds[j++] = _strtok(line, "\0\n");
				first_cmd = 0;
			}
			else
				cmds[j++] = _strtok(NULL, "\0\n");
		}
	}
	cmds[j] = NULL;
}

/**
 * logic_handler - splits the lines entered by the user using
 *	the "&&" and "||" delimiters and executes each token.
 * @state: a struct shell_state variable that stores the
 *	initial state of the shell program.
 * Return: Nothing.
 */
void logic_handler(shell_t *state)
{
	int i;
	int status = 0;
	char **cmds = state->logic_cmds;

	for (i = 0; cmds[i]; i++)
	{
		if (_strncmp(cmds[i], "&&", 2) == 0)
		{
			state->and_op = 1;
			state->or_op = 0;
		}
		else if (_strncmp(cmds[i], "||", 2) == 0)
		{
			state->and_op = 0;
			state->or_op = 1;
		}
		else
		{
			state->stripped_cmd = cmds[i];
			status = run_by_logic(state);
			state->status_code = status;
		}
	}
}

/**
 * run_by_logic - runs the command inputs based on the
 *	logical operators.
 * @state: a struct of type shell_state that stores the current
 *	state of the shell program.
 * Return: status for the new operation.
 */
int run_by_logic(shell_t *state)
{
	if (state->status_code == 0 && state->and_op)
		state->status_code = run_cmd(state);
	else if (state->status_code && state->or_op)
		state->status_code = run_cmd(state);
	else if (state->and_op == 0 && state->or_op == 0)
		state->status_code = run_cmd(state);
	return (state->status_code);
}
