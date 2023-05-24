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
		0, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, -2, NULL, NULL, NULL,
		0, 0, 0,
	};
	char *filename = NULL;

	state.ac = ac;
	state.av = av;
	/* initializes the environ and path linked lists */
	init_envp_list(&(state.envps));
	init_pathvp(&(state.path), state.envps);

	/* enters the shell loop state */
	if (ac == 1)
		interactive_loop(&state);
	else if (ac == 2)
	{
		/* frees the nodes of the environ and path linked list */
		filename = av[1];
		state.fd = open(filename, O_RDONLY);
		if (state.fd == -1)
		{
			if (errno == EACCES)
				return (126);
			if (errno == ENOENT)
			{
				printerr("ssss", av[0], ": 0: Can't open ", av[1], "\n");
				return (127);
			}
		}
		non_interactive(&state);
	}
	free_list(state.path);
	free_list(state.envps);
	free_list(state.aliases);

	return (state.status_code);
}
