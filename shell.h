#ifndef _SHELL_H_
#define _SHELL_H_

#define BUF_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;
/**
 * struct linkedlist_node - a node of a linkedlist that stores
 *	a string.
 * @id: an int that stores the current id of the node.
 * @str: a string field.
 * @next: a pointer to the next node in the linked list.
 */
typedef struct linkedlist_node
{
	unsigned int id;
	const char *str;
	struct linkedlist_node *next;
} record_t;

/**
 * struct shell_state - a struct the stores the current
 *	state of the shell program.
 * @ac: the number of arguments received by the shell program.
 * @av: an array of string arguments received by the shell.
 * @line: the string of commands entered by the user into the
 *	command line interface.
 * @cmd_path: stores a path to the executable shell program if found.
 * @cmds: an array of the string tokens of the line string.
 * @filename: the filename of a script.
 * @fd: a file descriptor to the filename.
 * @envps: a linkedlist of type record_t that stores the
 *	environment variable of the system.
 * @path: a linkedlist of type recored_t that stores the
 *	path variables of the system.
 * @aliases: a linkedlist of type record_t that stores the
 *	aliases for the shell.
 * @status_code: the current status code of the shell.
 */
typedef struct shell_state
{
	int ac;
	char **av;
	char *line;
	char *cmd_path;
	char **cmds;
	char *filename;
	int fd;
	record_t *envps;
	record_t *path;
	record_t *aliases;
	int status_code;
} shell_t;

/* std[in|out].c functions */
ssize_t _getline(char **lineptr, size_t *n, int fd);
int _putchar(const char c);
int _puts(const char *str);

/* string[1|2].c functions */
int _strlen(const char *str);
char *_strchr(char *str, const char c);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, char *src, const unsigned int n);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, const unsigned int n);
char *_strdup(char *src);
char *_memcpy(void *dest, const void *src, size_t n);

size_t _malloc_usable_size(void *ptr);
void *_realloc(void *old_blk, size_t size);

char *is_sys_cmd(char *cmd, record_t *pathenv);
char *append_file_to_dir(char *file, char *dir);

/* environ.c functions */
int init_envp_list(record_t **head);
int printenv(shell_t *state);
char *_getenv(record_t *head, const char *key);
int _setenv(shell_t *state, char *name, char *new_value);
int _unsetenv(shell_t *state);

int init_pathvp(record_t **pathenv, record_t *env);
record_t *init_path_list(record_t **head, const char *path);

record_t *add_node_to_tail(record_t **head, const char *str);
int delete_node_by_id(record_t **head, unsigned int id);
size_t index_list_by_id(const record_t *head);
size_t print_list(const record_t *head);
void free_list(record_t *head);

void construct(shell_t *state);

int tokenize(char *tokens[], char *str, const char *delim);

int execute(shell_t *state);
int run_cmd(shell_t *state);

int _cddir(shell_t *state);
#endif
