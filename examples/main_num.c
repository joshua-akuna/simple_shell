#include "shell.h"

int main(void)
{
	char *res;
	int num = -9847483;

	res = _itoa(num);
	res = res ? res : "nil";
	printf("%s\n", res);

	num = _atoi("-12345");
	printf("%i\n", num);

	free(res);
	return (0);
}
