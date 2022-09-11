#include "huffman.h"
#include <stdlib.h>

/**
 * symbol_create - creates a symbol
 * @data: data
 * @freq: frecuency
 * Return: symbol_t
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbolpointer = NULL;

	symbolpointer = malloc(sizeof(symbol_t));
	if (!symbolpointer)
		return (NULL);

	symbolpointer->data = data;
	symbolpointer->freq = freq;

	return (symbolpointer);
}
