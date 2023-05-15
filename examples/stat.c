#include "../shell.h"

/**
 * main - stat example.
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	unsigned int i, nstatus;
	struct stat st;

	if (ac < 2)
	{
		dprintf(
			STDERR_FILENO,
			"Usage: %s path_to_file ....\n",
			av[0]
		);
		return (1);
	}

	i = 1;
	while (av[i])
	{
		printf("%s:", av[i]);
		nstatus = stat(av[i], &st);
		if (nstatus == 0)
			printf(" FOUND\n");
		else
			printf(" NOT FOUND\n");
		i++;
	}
	return (0);
}
