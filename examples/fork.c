#include "../shell.h"

/**
 * main - fork example.
 * Return: Always 0.
 */
int main(void)
{
	pid_t fpid;
	pid_t pid;

	printf("Before fork\n");

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}

	printf("After fork\n");

	fpid = getpid();

	printf("My pid is %u\n", fpid);

	return (0);
}
