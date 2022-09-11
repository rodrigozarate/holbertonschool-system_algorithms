#include "huffman.h"

/**
 * huffman_tree - huffman tree
 * @data: data
 * @freq: frequency
 * @size: array size
 * Return: pointer node
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *hPQ = NULL;
	binary_tree_node_t *hT = NULL;

	if (!data || !freq || size == 0)
		return (NULL);

	hPQ = huffman_priority_queue(data, freq, size);
	if (!hPQ)
		return (NULL);

	/* extraction/summing/insertion cycles in queue until one node left */
	while (hPQ->root && (hPQ->root->left || hPQ->root->right))
	{
		if (!huffman_extract_and_insert(hPQ))
		{
			heap_delete(hPQ, fNestNd);
			return (NULL);
		}
	}

	hT = (binary_tree_node_t *)(hPQ->root->data);
	heap_delete(hPQ, NULL);

	return (hT);
}
