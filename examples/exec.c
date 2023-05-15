#include "../shell.h"
/**
 * main - execve example.
 * Return: Always 0.
 */
int main(void)
{
	char *av[] = {"/bin/ls", "-l", "/usr/", NULL};
	int err = 0;

	printf("Before execve\n");

	err = execve(av[0], av, NULL);
	if (err == -1)
		perror("Error");
	printf("status code: %d\n", err);

	printf("After execve\n");

	return (0);
}
