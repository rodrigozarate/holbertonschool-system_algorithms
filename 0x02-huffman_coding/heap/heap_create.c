#include "heap.h"
#include <stdlib.h>

/**
 * heap_create - guess what it creates the heap data structure
 *
 * @data_cmp: pointer
 * Return: pointer
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *new = NULL;

	new = malloc(sizeof(heap_t));
	if (!new)
		return (NULL);

	new->size = 0;
	new->data_cmp = data_cmp;
	new->root = NULL;

	return (new);
}