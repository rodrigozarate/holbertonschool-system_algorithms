#include "rb_trees.h"


/**
 * rb_tree_get_uncle - retrieves sibling
 * @n: starting node
 * Return: pointer
 */
rb_tree_t *rb_tree_get_uncle(rb_tree_t *n)
{
	rb_tree_t *p = n ? n->parent : NULL;

	if (!p || !p->parent)
		return (NULL);

	if (p == p->parent->left)
		return (p->parent->right);

	return (p->parent->left);
}

/**
 * rb_tree_rotate_left - left child of root becomes new root, tree rotated
 * @tree: pointer
 * Return: new root node
 */
rb_tree_t *rb_tree_rotate_left(rb_tree_t *tree)
{
	rb_tree_t *pivot = NULL;

	if (!tree)
		return (NULL);

	pivot = tree->right;

	tree->right = pivot->left;
	if (pivot->left)
		pivot->left->parent = tree;

	pivot->parent = tree->parent;
	if (tree->parent)
	{
		if (tree == tree->parent->left)
			tree->parent->left = pivot;
		else
			tree->parent->right = pivot;
	}

	pivot->left = tree;
	tree->parent = pivot;

	return (pivot);
}


/**
 * rb_tree_rotate_right - tree rotated
 * @tree: pointer
 * Return: new root node
 */
rb_tree_t *rb_tree_rotate_right(rb_tree_t *tree)
{
	rb_tree_t *pivot = NULL;

	if (!tree)
		return (NULL);

	pivot = tree->left;

	tree->left = pivot->right;
	if (pivot->right)
		pivot->right->parent = tree;

	pivot->parent = tree->parent;
	if (tree->parent)
	{
		if (tree == tree->parent->right)
			tree->parent->right = pivot;
		else
			tree->parent->left = pivot;
	}

	pivot->right = tree;
	tree->parent = pivot;

	return (pivot);
}


/**
 * rb_tree_insert_case4 - case 4
 * @node: pointer
 * Return: new root node
 */
rb_tree_t *rb_tree_insert_case4(rb_tree_t *node)
{
	rb_tree_t *p = node ? node->parent : NULL;
	rb_tree_t *g = p ? p->parent : NULL;
	rb_tree_t *new_root = NULL;

	if (!p || !g)
		return (NULL);

	if (node == p->right && p == g->left)
	{
		new_root = rb_tree_rotate_left(p);
		node = node->left;
	}

	else if (node == p->left && p == g->right)
	{
		new_root = rb_tree_rotate_right(p);
		node = node->right;
	}

	p = node ? node->parent : NULL;
	g = p ? p->parent : NULL;

	if (node == p->left)
		new_root = rb_tree_rotate_right(g);
	else
		new_root = rb_tree_rotate_left(g);

	while (new_root && new_root->parent)
		new_root = new_root->parent;

	p->color = BLACK;
	g->color = RED;

	return (new_root);
}


/**
 * rb_tree_insert_repair - color repair
 * @root: pointer
 * @node: pointer
 * Return: new root node
 */
rb_tree_t *rb_tree_insert_repair(rb_tree_t *root, rb_tree_t *node)
{
	if (!node)
		return (root);

	if (node->parent == NULL)
	{
		node->color = BLACK;
		return (node);
	}
	else if (node->parent->color == BLACK)
	{
		return (root);
	}
	else if (rb_tree_get_uncle(node) != NULL &&
		 rb_tree_get_uncle(node)->color == RED)
	{
		node->parent->color = BLACK;
		rb_tree_get_uncle(node)->color = BLACK;
		node->parent->parent->color = RED;
		return (rb_tree_insert_repair(root, node->parent->parent));
	}

	return (rb_tree_insert_case4(node));

}


/**
 * rb_tree_insert_recurse - insert node
 * @tree: pointer
 * @value: int
 * Return: new node
 */
rb_tree_t *rb_tree_insert_recurse(rb_tree_t *tree, int value)
{
	rb_tree_t *new = NULL;

	if (tree)
	{
		if (tree->n > value)
		{
			if (tree->left == NULL)
			{
				new = rb_tree_node(tree, value, RED);
				tree->left = new;
				return (new);
			}

			return (rb_tree_insert_recurse(tree->left, value));
		}

		if (tree->n < value)
		{
			if (tree->right == NULL)
			{
				new = rb_tree_node(tree, value, RED);
				tree->right = new;
				return (new);
			}

			return (rb_tree_insert_recurse(tree->right, value));
		}

		return (NULL);
	}

	return (rb_tree_node(NULL, value, RED));
}


/**
 * rb_tree_insert - insert
 *
 * @tree: pointer
 * @value: int
 * Return: new node
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new = NULL, *new_root = NULL;

	if (!tree)
		new = rb_tree_insert_recurse(NULL, value);
	else
		new = rb_tree_insert_recurse(*tree, value);

	if (!new)
		return (NULL);

	new_root = rb_tree_insert_repair(*tree, new);
	if (!new_root)
		return (NULL);

	*tree = new_root;

	return (new);
}
