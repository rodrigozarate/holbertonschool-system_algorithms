#include "nary_trees.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * nary_tree_insert - inserts node
 * @parent: pointer
 * @str: string
 * Return: pointer or NULL
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *new;
	char *str_copy;

	new = malloc(sizeof(nary_tree_t));
	if (!new)
	{
		fprintf(stderr, "nary_tree_insert: malloc error\n");
		return (NULL);
	}

	str_copy = strdup(str);
	if (!str_copy)
	{
		free(new);
		fprintf(stderr, "nary_tree_insert: strdup error\n");
		return (NULL);
	}

	new->content = str_copy;
	new->parent = parent;
	new->nb_children = 0;
	new->children = NULL;
	new->next = NULL;

	if (parent)
	{
		new->next = parent->children;
		parent->children = new;
		parent->nb_children++;
	}

	return (new);
}
