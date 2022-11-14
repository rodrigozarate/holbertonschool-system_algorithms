#include "nary_trees.h"
#include <stdlib.h>


/**
 * nary_tree_delete - deallocates tree
 * @tree: pointer
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *temp;

	if (!tree)
		return;

	while (tree->children)
	{
		temp = tree->children;
		tree->children = tree->children->next;
		nary_tree_delete(temp);
	}

	if (tree->content)
		free(tree->content);

	free(tree);
}
