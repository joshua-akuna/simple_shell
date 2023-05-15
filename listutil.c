#include "shell.h"

/**
 * add_node_to_tail - adds a new node to the tail
 *	of the linkedlist.
 * @head: a pointer to the head of the linkedlist.
 * @str: a pointer to a string argument.
 * Return: the pointer to the newly created node.
 */
record_t *add_node_to_tail(record_t **head, const char *str)
{
	record_t *new_node = NULL;
	record_t *tail;

	if (str && head)
	{
		new_node = malloc(sizeof(record_t));
		if (new_node == NULL)
			return (NULL);
		new_node->id = 0;
		new_node->str = _strdup((char *)str);
		new_node->next = NULL;

		if (*head == NULL)
			*head = new_node;
		else
		{
			tail = *head;
			while (tail->next != NULL)
				tail = tail->next;
			tail->next = new_node;
		}
		index_list_by_id(*head);
	}
	return (new_node);
}

/**
 * delete_node_by_id - finds a node of type record_t by it
 *	id field and removes it from the linked list.
 * @head: a struct record_t type pointer to the
 *	first node of the linked list.
 * @id: the id of the node to delete.
 * Return: 0 if successful else -1.
 */
int delete_node_by_id(record_t **head, unsigned int id)
{
	record_t *prev_node;
	record_t *node_to_delete;

	if (head == NULL || *head == NULL)
		return (-1);

	if (id == 0)
	{
		node_to_delete = *head;
		*head = (*head)->next;
	}
	else if (id > 0)
	{
		prev_node = *head;
		while  (prev_node && prev_node->next
				&& prev_node->next->id != id)
			prev_node = prev_node->next;

		if (prev_node == NULL || prev_node->next == NULL)
			return (-1);

		node_to_delete = prev_node->next;
		prev_node->next = prev_node->next->next;
	}
	printf("%i: %s\n", node_to_delete->id, node_to_delete->str);
	index_list_by_id(*head);
	free((char *)node_to_delete->str);
	free(node_to_delete);
	return (0);
}

/**
 * free_list - frees all dynamically allocated memory space
 *	and nodes of a linked list recursively.
 * @head: a pointer to the head node of the linked list.
 * Return: Nothing.
 */
void free_list(record_t *head)
{
	char *str = NULL;

	if (head == NULL)
		return;

	free_list(head->next);
	str = (char *)head->str;
	free(str);
	free(head);
}

/**
 * print_list - prints the string content of the str
 *	property of the record_t struct instance.
 * @head: a pointer to the head node of linked list node
 *	of record_t type.
 * Return: number of nodes in the list printed.
 */
size_t print_list(const record_t *head)
{
	char *str = NULL;

	(void)str;
	if (head == NULL)
		return (0);
	str = (char *)head->str;
	/*_puts(str);*/
	printf("%i: %s\n", head->id, head->str);
	return (1 + (print_list(head->next)));
}

/**
 * index_list_by_id - prints the string content of the str
 *	property of the record_t struct instance.
 * @head: a pointer to the head node of linked list node
 *	of record_t type.
 * Return: the id of the last node.
 */
size_t index_list_by_id(const record_t *head)
{
	size_t id = 0;
	record_t *node = (record_t *)head;

	while (node)
	{
		node->id = id++;
		node = node->next;
	}

	return (id);
}
