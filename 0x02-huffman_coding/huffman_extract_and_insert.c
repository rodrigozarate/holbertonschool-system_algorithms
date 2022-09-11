#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * hSN - node sum
 * @ex_node1: node
 * @ex_node2: node
 * Return: pointer node
 */
binary_tree_node_t *hSN(binary_tree_node_t *ex_node1,
						binary_tree_node_t *ex_node2)
{
	binary_tree_node_t *sum_node = NULL;
	symbol_t *sum_sym = NULL;
	size_t sum_freq;

	if (!ex_node1 || !ex_node2)
		return (NULL);

	sum_freq = ((symbol_t *)(ex_node1->data))->freq +
		((symbol_t *)(ex_node2->data))->freq;

	sum_sym = symbol_create(-1, sum_freq);
	if (!sum_sym)
		return (NULL);

	sum_node = binary_tree_node(NULL, sum_sym);
	if (!sum_node)
	{
		free(sum_sym);
		return (NULL);
	}

	return (sum_node);
}

/**
 * huffman_extract_and_insert - extract and insert
 * @priority_queue: heap_t
 * Return: int
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	void *ex_data1 = NULL, *ex_data2 = NULL;
	binary_tree_node_t *sum_node = NULL,
		*ex_node1 = NULL, *ex_node2 = NULL;

	if (!priority_queue || !priority_queue->root ||
		!priority_queue->root->data)
		return (0);

	priority_queue->data_cmp = nSymComp;

	ex_data1 = heap_extract(priority_queue);
	ex_node1 = (binary_tree_node_t *)ex_data1;
	ex_data2 = heap_extract(priority_queue);
	ex_node2 = (binary_tree_node_t *)ex_data2;
	if (!ex_node1 || !ex_node2)
		return (0);

	sum_node = hSN(ex_node1, ex_node2);
	if (!sum_node)
		return (0);

	if (!heap_insert(priority_queue, sum_node))
	{
		free(sum_node->data);
		free(sum_node);
		return (0);
	}

	sum_node->left = ex_node1;
	ex_node1->parent = sum_node;
	sum_node->right = ex_node2;
	ex_node2->parent = sum_node;

	return (1);
}
