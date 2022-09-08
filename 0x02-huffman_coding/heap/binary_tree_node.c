#include "heap.h"
#include <stdlib.h>


/**
 * binary_tree_node - creates a tree
 * @parent: pointer
 * @data: data
 * Return: pointer
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new = NULL;

	new = malloc(sizeof(binary_tree_node_t));
	if (!new)
		return (NULL);

	new->data = data;
	new->left = NULL;
	new->right = NULL;
	new->parent = parent;

	return (new);
}
