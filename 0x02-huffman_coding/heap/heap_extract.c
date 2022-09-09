#include "heap.h"
#include <stdlib.h>


/**
 * bTS - size
 * @tree: root node
 * Return: size_t
 */
size_t bTS(const binary_tree_node_t *tree)
{
	if (!tree)
		return (0);

	if (!tree->left && !tree->right)
		return (1);

	return (1 + bTS(tree->left) +
		bTS(tree->right));
}


/**
 * bTIC - checks binary completion
 * @tree: root node
 * @node_i: iterator
 * @tree_sz: tree_sz
 * Return: int
 */
int bTIC(const binary_tree_node_t *tree, size_t node_i, size_t tree_sz)
{
	if (!tree)
		return (1);

	if (node_i >= tree_sz)
		return (0);

	return (bTIC(tree->left, (2 * node_i) + 1, tree_sz) &&
		bTIC(tree->right, (2 * node_i) + 2, tree_sz));
}


/**
 * lILO - last level order
 * @root: pointer
 * Return: pointer
 */
binary_tree_node_t *lILO(binary_tree_node_t *root)
{
	binary_tree_node_t *last = NULL;
	bt_node_queue_t *queue = NULL;

	if (!root || !bTIC(root, 0, bTS(root)))
		return (NULL);

	queue = BTQP(&queue, root);
	if (!queue)
		return (NULL);

	while (queue)
	{
		if ((queue->node->left && !BTQP(&queue, queue->node->left)) ||
		    (queue->node->right && !BTQP(&queue, queue->node->right)))
		{
			BTQC(&queue);
			return (NULL);
		}

		if (!queue->next)
		{
			if (queue->node->left)
				last = queue->node->left;
			else
				last = queue->node;
		}

		BTQA(&queue);
	}

	return (last);
}


/**
 * minHSD - sift down
 * @root: pointer
 * @data_cmp: pointer
 */
void minHSD(binary_tree_node_t *root, int (data_cmp)(void *, void *))
{
	binary_tree_node_t *temp = NULL, *next = NULL;
	void *swap;

	if (!data_cmp)
		return;

	temp = root;
	while (temp && temp->left)
	{
		if (!temp->right ||
		    data_cmp(temp->left->data, temp->right->data) <= 0)
		{
			if (data_cmp(temp->data, temp->left->data) >= 0)
				next = temp->left;
			else
				break;
		}
		else if (data_cmp(temp->data, temp->right->data) >= 0)
			next = temp->right;
		else
			break;

		if (next)
		{
			swap = temp->data;
			temp->data = next->data;
			next->data = swap;
		}

		temp = next;
	}
}


/**
 * hE - extacts heap
 * @root: pointer
 * @data_cmp: pointer
 * Return: pointer
 */
void *hE(binary_tree_node_t **root, int (data_cmp)(void *, void *))
{
	binary_tree_node_t *last = NULL;
	void *extract = NULL;

	if (!root || !data_cmp)
		return (NULL);

	last = lILO(*root);
	if (!last)
		return (NULL);

	extract = (*root)->data;
	(*root)->data = last->data;

	minHSD(*root, data_cmp);

	if (last->parent)
	{
		if (last->parent->left == last)
			last->parent->left = NULL;
		else if (last->parent->right == last)
			last->parent->right = NULL;
	}

	if (last == *root)
		*root = NULL;
	free(last);

	return (extract);
}


/**
 * heap_extract - extract
 * @heap: pointer
 * Return: pointer
 */
void *heap_extract(heap_t *heap)
{
	void *extract = NULL;

	if (!heap || !heap->data_cmp || !heap->root)
		return (NULL);

	extract = hE(&(heap->root), heap->data_cmp);
	if (extract != NULL)
		heap->size--;

	return (extract);
}
