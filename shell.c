#include "shell.h"

int infinite_loop(shell_t *state);
/**
 * main - the main shell progrma.
 * @av: an array of string arguments.
 * @ac: the number of arguments in av.
 * Return: 0 if successful.
 */
int main(int ac, char **av)
{
	char *filename == NULL;

	shell_t state = {
		0, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, -2, NULL, NULL, NULL,
		0, 0, 0,
	};

	state.ac = ac;
	state.av = av;

	if (ac == 2)
	{
		filename = av[1];
		state->fd = open(filename, RDONLY);
		if (state->fd == -1)
		{

		}
	}
	/* initializes the environ and path linked lists */
	init_envp_list(&(state.envps));
	init_pathvp(&(state.path), state.envps);
	/* enters the shell loop state */
	if (state.ac == 1)
		infinite_loop(&state);
	else if (state.ac == 2)
		non_interactive(&state);
	/* frees the nodes of the environ and path linked list */
	free_list(state.path);
	free_list(state.envps);
	free_list(state.aliases);
	return (0);
}
