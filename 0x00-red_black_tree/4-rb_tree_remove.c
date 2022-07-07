#include "rb_trees.h"

/**
 * rb_tree_remove - remove node from red black tree
 * @root: pointer
 * @n: value
 * Return: pointer
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	int flag;

	flag = 0;
	root = rb_tree_remove_r(root, n, &flag);
	if (root != NULL)
		root->color = BLACK;

	return (root);
}

/**
 * rb_tree_remove_r - recursion deleter
 * @root: pointer
 * @n: value
 * @flag: finish flag
 * Return: root
 */
rb_tree_t *rb_tree_remove_r(rb_tree_t *root, int n, int *flag)
{
	int direction;
	rb_tree_t *save = NULL;

	if (root == NULL)
		*flag = 1;
	else
	{
		if (n == root->n)
		{
			if (root->left == NULL || root->right == NULL)
			{
				if (root->left == NULL)
					save = root->right;
				if (IS_RED(root))
					*flag = 1;
				else if (IS_RED(save))
				{
					save->color = BLACK;
					*flag = 1;
				}
				free(root);
				return (save);
			}
			else
			{
				save = root->left;
				while (save->right != NULL)
					save = save->right;
				root->n = save->n;
				n = save->n;
			}
		}
		direction = remove_recurse_direction_helper(root, n, flag);
		if (!*flag)
			root = rb_rebalance(root, direction, flag);
	}
	return (root);
}

/**
 * remove_recurse_direction_helper - set direction of recursion
 * @root: pointer
 * @n: value
 * @flag: finish flag
 * Return: direction
 */
int remove_recurse_direction_helper(rb_tree_t *root, int n, int *flag)
{
	int direction;

	if (n > root->n)
	{
		direction = 1;
		root->right = rb_tree_remove_r(root->right, n, flag);
		if (root->right != NULL)
			root->right->parent = root;
	}
	else
	{
		direction = 0;
		root->left = rb_tree_remove_r(root->left, n, flag);
		if (root->left != NULL)
			root->left->parent = root;
	}

	return (direction);
}

/**
 * rb_rebalance - rebalance tree
 * @root: pointer
 * @direction: direction int
 * @flag: flag
 * Return: node root
 */
rb_tree_t *rb_rebalance(rb_tree_t *root, int direction, int *flag)
{
	rb_tree_t *p;
	rb_tree_t *s;

	p = root;
	if (direction)
		s = root->left;
	else
		s = root->right;

	if (IS_RED(s))
	{
		root = single_rotation(root, direction);
		if (direction)
			s = p->left;
		else
			s = p->right;
	}
	if (s != NULL)
	{
		if (!IS_RED(s->left) && !IS_RED(s->right))
		{
			if (IS_RED(p))
				*flag = 1;

			p->color = BLACK;
			s->color = RED;
		}
		else
			rebalance_red_siblings(direction, p, s, root, flag);
	}
	return (root);
}

/**
 * rebalance_red_siblings - rebalance
 * @direction: direction
 * @p: pointer
 * @s: pointer
 * @root: pointer
 * @flag: flag
 */
void rebalance_red_siblings(
	int direction, rb_tree_t *p, rb_tree_t *s, rb_tree_t *root, int *flag)
{
	rb_color_t save_color = p->color;
	int new_root = (root == p);

	if (direction)
	{
		if (IS_RED(s->left))
			p = single_rotation(p, direction);
		else
			p = double_rotation(p, direction);
	}
	else
	{
		if (IS_RED(s->right))
			p = single_rotation(p, direction);
		else
			p = double_rotation(p, direction);
	}
	p->color = save_color;
	p->left->color = BLACK;
	p->right->color = BLACK;
	if (new_root)
		root = p;
	else
	{
		if (direction)
			root->right = p;
		else
			root->left = p;
	}
	*flag = 1;
}

/**
 * single_rotation -single rotation
 * @root: pointer
 * @direction: direction
 * Return: pointer
 */
rb_tree_t *single_rotation(rb_tree_t *root, int direction)
{
	rb_tree_t *tmp;

	if (direction)
	{
		tmp = root->left;
		root->left = tmp->right;
		tmp->right = root;
		tmp->parent = root->parent;
		root->parent = tmp;
	}
	else
	{
		tmp = root->right;
		root->right = tmp->left;
		tmp->left = root;
		tmp->parent = root->parent;
		root->parent = tmp;
	}
	root->color = RED;
	tmp->color = BLACK;
	return (tmp);
}

/**
 * double_rotation - double rotation
 * @root: pointer
 * @direction: direction
 * Return: pointer to tmp root node
 */
rb_tree_t *double_rotation(rb_tree_t *root, int direction)
{
	if (direction)
		root->left = single_rotation(root->left, !direction);
	else
		root->right = single_rotation(root->right, !direction);
	return (single_rotation(root, direction));
}
