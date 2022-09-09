#include "heap.h"
#include <stdlib.h>

/**
 * bTD - binary tree deleter
 * @tree: pointer
 * @free_data: poiniter
 */
void bTD(binary_tree_node_t *tree, void (*free_data)(void *))
{
	if (!tree)
		return;

	bTD(tree->left, free_data);
	bTD(tree->right, free_data);

	if (free_data)
		free_data(tree->data);
	free(tree);
}

/**
 * heap_delete - delete heap
 * @heap: heap pointer
 * @free_data: pointer
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	bTD(heap->root, free_data);

	free(heap);
}
