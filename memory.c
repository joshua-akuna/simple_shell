#include "shell.h"
/**
 * _realloc - resize a previously reallocated
 *	malloc'd block of memory..
 * @old_blk : a pointer to the malloc'd memory to reallocate.
 * @new_size: the new size of the reallocated block.
 * Return: a pointer to the newly reallocated memory space
 *	else NULL if unsuccessful.
 */
void *_realloc(void *old_blk, size_t new_size)
{
	void *new_blk = NULL;
	size_t old_size, actual_size;

	/* if ptr is NULL, return an equivalent of malloc(size) */
	if (old_blk == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(old_blk);
		return (new_blk);
	}
	new_blk = malloc(new_size);
	if (new_blk == NULL) /* if malloc fails */
		return (NULL);
	/* copies the contents of the old memory to the new one */
	old_size = _malloc_usable_size(old_blk);
	actual_size = old_size < new_size ? old_size : new_size;
	memcpy(new_blk, old_blk, actual_size);
	/* free the old memory block */
	free(old_blk);

	return (new_blk);
}

/**
 * _malloc_usable_size - determines the number of bytes that was
 *	allocated for a malloc'd memory block.
 * @ptr: a pointer to the malloc'd memory block.
 * Return: the number of allocated bytes.
 */
size_t _malloc_usable_size(void *ptr)
{
	/* size of the header for the memory block */
	size_t header_size;
	size_t *blk_header;
	size_t usable_size = 0;

	if (ptr == NULL)
		return (usable_size);

	/* size of the block header */
	header_size = sizeof(uintptr_t);
	/* subtract the header size from the ptr to get the size field */
	blk_header = (uintptr_t *)ptr - 1;
	usable_size = *blk_header - header_size;

	return (usable_size);
}
