#include "shell.h"

int main(void)
{
	char *dest = strdup("name");
	char *src = strdup(" is joshua");
	char *res = NULL;

	res = append_file_to_dir(dest, src);
	if (res)
	{
		printf("%s\n", res);
		free(res);
	}
	free(dest);
	free(src);
	return (0);
}
