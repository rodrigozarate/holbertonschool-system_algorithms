#ifndef _HUFF_MAN_
#define _HUFF_MAN_

#include <stddef.h>

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

#endif
