#include "rb_trees.h"
#include <limits.h>

/**
 * BiggerSizeT - define the bigger
 * @w: value one
 * @h: value two
 * Return: bigger
 */
size_t BiggerSizeT(size_t w, size_t h)
{
	return ((w > h) ? w : h);
}

/**
 * TreeHeight - measure height
 * @tree: pointer
 * Return: int
 */
size_t TreeHeight(const rb_tree_t *tree)
{
	if (!tree)
		return (1);

	if (tree->color == BLACK)
		return (1 + BiggerSizeT(TreeHeight(tree->left),
								TreeHeight(tree->right)));
	else
		return (BiggerSizeT(TreeHeight(tree->left),
								TreeHeight(tree->right)));
}

/**
 * ColorTest - Color test
 * @tree: pointer
 * Return: 1 if color ok
 */
int ColorTest(const rb_tree_t *tree)
{
	if (tree)
	{
		if (tree->color != RED && tree->color != BLACK)
			return (0);

		if (!(tree->parent))
		{
			if (tree->color != BLACK)
				return (0);
		}
		else if (tree->color == RED)
		{
			if (tree->parent->color == RED ||
				(tree->left && tree->left->color == RED) ||
				(tree->right && tree->right->color == RED))
				return (0);
		}
		if (TreeHeight(tree->left) !=
			TreeHeight(tree->right))
			return (0);

		return (ColorTest(tree->left) &&
				ColorTest(tree->right));
	}
}

/**
 * BinarySearchTree - validate Binary Search Tree
 * @tree: pointer
 * @node: pointer
 * Return: 1 if true
 */
int BinarySearchTree(const rb_tree_t *tree, int *node)
{
	if (tree)
	{
		if (!BinarySearchTree(tree->left, node))
			return (0);

		if (tree->n <= *node)
			return (0);

		*node = tree->n;

		return (BinarySearchTree(tree->right, node));
	}
	return (1);
}

/**
* rb_tree_is_valid - checks if a binary tree is a valid Red-Black Tree
* @tree: pointer to root node of tree
* Return: 1 if true 0 else
*/
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int node = INT_MIN;

	if (!tree)
		return (0);

	if (!BinarySearchTree(tree, &node))
		return (0);

	return (RedBlackColor(tree));
}
