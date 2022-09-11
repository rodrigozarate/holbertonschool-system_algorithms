#include "huffman.h"
#include <stdlib.h>

/**
 * nSymComp - compare nested symbols
 * @s1: symbol
 * @s2: symbol
 * Return: 0 1 2
 */
int nSymComp(void *s1, void *s2)
{
	binary_tree_node_t *node1, *node2;
	symbol_t *symbol1, *symbol2;
	size_t freq1, freq2;

	node1 = (binary_tree_node_t *)s1;
	node2 = (binary_tree_node_t *)s2;

	symbol1 = node1 ? (symbol_t *)(node1->data) : NULL;
	symbol2 = node2 ? (symbol_t *)(node2->data) : NULL;

	freq1 = symbol1 ? symbol1->freq : 0;
	freq2 = symbol2 ? symbol2->freq : 0;

	return (freq1 - freq2);
}

/**
 * fNestNd - free nested node
 * @data: data
 */
void fNestNd(void *data)
{
	binary_tree_node_t *n_data = NULL;
	symbol_t *s_data = NULL;

	n_data = (binary_tree_node_t *)data;

	if (n_data)
	{
		s_data = (symbol_t *)(n_data->data);

		if (s_data)
			free(s_data);

		free(n_data);
	}
}

/**
 * huffman_priority_queue - huffman_priority_queue
 * @data: char
 * @freq: frecuency
 * @size: array size
 * Return: pointer
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *nn_node = NULL, *prio_que_node = NULL;
	heap_t *priority_queue = NULL;
	symbol_t *symbol = NULL;
	size_t i;

	if (!data || !freq || size == 0)
		return (NULL);

	priority_queue = heap_create(nSymComp);
	if (!priority_queue)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		nn_node = binary_tree_node(NULL, symbol);
		prio_que_node = heap_insert(priority_queue, nn_node);

		if (!symbol || !nn_node || !prio_que_node)
		{
			heap_delete(priority_queue, fNestNd);
			return (NULL);
		}
	}

	return (priority_queue);
}
