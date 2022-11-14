#include "nary_trees.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * find_diameter - finds the diameter
 * @root: pointer
 * @depth: depth
 * @diameter: pointer
 * Return: pointer or NULL
 */
size_t find_diameter(nary_tree_t const *root, size_t depth, size_t *diameter)
{
	size_t *child_depths = NULL, i, max_depth_1, max_depth_2, node_diam;
	nary_tree_t *temp;

	if (!diameter)
		fprintf(stderr, "find_diameter: error\n");
	if (!root || !diameter)
		return (0);

	max_depth_1 = max_depth_2 = depth;
	if (root->nb_children)
	{
		child_depths = malloc(sizeof(size_t) * root->nb_children);
		if (!child_depths)
		{
			fprintf(stderr, "find_diameter: malloc error\n");
			return (0);
		}

		for (temp = root->children, i = 0; temp && i < root->nb_children;
		     temp = temp->next, i++)
			child_depths[i] = find_diameter(temp, depth + 1, diameter);

		for (i = 0; i < root->nb_children; i++)
		{
			if (child_depths[i] > max_depth_1)
				max_depth_1 = child_depths[i];
			else if (child_depths[i] > max_depth_2)
				max_depth_2 = child_depths[i];
		}
		free(child_depths);
	}

	node_diam = (max_depth_1 - depth) + (max_depth_2 - depth) + 1;
	if (node_diam > *diameter)
		*diameter = node_diam;
	return (max_depth_1);
}


/**
 * nary_tree_diameter - finds diameter of an N-ary tree
 * @root: pointer
 * Return: diameter or 0
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	find_diameter(root, 0, &diameter);

	return (diameter);
}
