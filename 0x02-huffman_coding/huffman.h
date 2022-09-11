#ifndef _HUFF_MAN_
#define _HUFF_MAN_

#include <stddef.h>
#include "heap/heap.h"

/**
 * struct symbol_s - structure
 * @data: data
 * @freq: frecuency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

symbol_t *symbol_create(char data, size_t freq);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
void fNestNd(void *data);
int nSymComp(void *s1, void *s2);
int huffman_extract_and_insert(heap_t *priority_queue);
binary_tree_node_t *hSN(binary_tree_node_t *ex_node1,
						binary_tree_node_t *ex_node2);
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);

#endif
