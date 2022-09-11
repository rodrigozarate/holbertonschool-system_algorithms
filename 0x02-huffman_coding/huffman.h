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

#endif
