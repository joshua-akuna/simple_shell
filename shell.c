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
	shell_t state = {
		0, NULL, NULL, NULL, NULL, NULL, -2, NULL, NULL, NULL, 0
	};

	state.ac = ac;
	state.av = av;
	/* initializes the environ and path linked lists */
	init_envp_list(&(state.envps));
	init_pathvp(&(state.path), state.envps);
	/* enters the shell loop state */
	infinite_loop(&state);
	/* frees the nodes of the environ and path linked list */
	free_list(state.path);
	free_list(state.envps);

	return (0);
}
