#include "nary_trees.h"
#include <stdio.h>


/**
 * nary_tree_search - search each node
 * @root: pointer
 * @action: pointer to function
 *   Its arguments are:
 *     node: pointer
 *     depth: depth
 * @_depth: current depth in tree of `root`
 * Return: max depth
 */
size_t nary_tree_search(nary_tree_t const *root,
			void (*action)(nary_tree_t const *node, size_t depth),
			size_t _depth)
{
	nary_tree_t *temp;
	size_t child_ct, max_depth, branch_depth;

	if (!action)
		fprintf(stderr, "nary_tree_search: NULL function given\n");

	if (!root || !action)
		return (_depth ? _depth - 1 : 0);

	action(root, _depth);

	max_depth = 0;
	for (temp = root->children, child_ct = 0;
	     temp && child_ct < root->nb_children;
	     temp = temp->next, child_ct++)
	{
		branch_depth = nary_tree_search(temp, action, _depth + 1);
		if (branch_depth > max_depth)
			max_depth = branch_depth;
	}

	return (max_depth);
}

/**
 * nary_tree_traverse - walks through an N-ary tree, node by node
 * @root: pointer to the root node of the tree to traverse
 * @action: pointer to a function to execute for each node being traversed,
 *   Its arguments are:
 *     node: pointer to the node being traversed
 *     depth: depth of the node being traversed
 * Return: int size_t the biggest depth of the tree pointed to by root
 */
size_t nary_tree_traverse(nary_tree_t const *root,
			void (*action)(nary_tree_t const *node, size_t depth))
{
	if (!action)
	{
		fprintf(stderr, "nary_tree_traverse: NULL function given\n");
		return (0);
	}

	return (nary_tree_search(root, action, 0));
}
