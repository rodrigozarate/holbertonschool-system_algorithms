#include "nary_trees.h"
#include <string.h>
#include <stdio.h>


/**
 * check_path - checks if a path exists in an N-ary tree
 * @root: pointer
 * @path: array path to test
 * @pidx: index recursion frame
 * Return: 1 or 0 on failure
 */
int check_path(nary_tree_t const *root, char const * const *path, size_t pidx)
{
	nary_tree_t *temp;

	if (!root || !root->content || path == NULL)
	{
		fprintf(stderr, "check_path: NULL parameter given\n");
		return (0);
	}

	if (strncmp(root->content, path[pidx], strlen(root->content) + 1) != 0)
		return (0);

	if (path[pidx + 1] == NULL)
		return (1);

	for (temp = root->children; temp; temp = temp->next)
	{
		if (check_path(temp, path, pidx + 1))
			return (1);
	}

	return (0);
}


/**
 * path_exists - checks if a path exists
 * @root: pointer
 * @path: array path to test
 *
 * Return: 1 or 0 on failure
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	if (!root || !path || !path[0])
		return (0);

	return (check_path(root, path, 0));
}
