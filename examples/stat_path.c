#include "../shell.h"
/**
 * validate_cmd_in_stat - check if the path is a valid path.
 * Return: a path if it is valid else NULL.
 */
char *validate_cmd_in_stat(char *cmd)
{
	int i;
	char *path = NULL;
	char *path_vars[128];

	/* get the PATH variable */
	path = getenv("PATH");
}
