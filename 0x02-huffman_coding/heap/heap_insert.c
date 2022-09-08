#include "heap.h"
#include <stdlib.h>


/**
 * BTQP - add node
 * @queue: pointer
 * @node: pointer
 * Return: pointer
 */
bt_node_queue_t *BTQP(bt_node_queue_t **queue, binary_tree_node_t *node)
{
	bt_node_queue_t *temp, *new = NULL;

	if (!queue || !node)
		return (NULL);

	new = malloc(sizeof(bt_node_queue_t));
	if (!new)
		return (NULL);
	new->node = node;
	new->next = NULL;

	if (!*queue)
		*queue = new;
	else
	{
		temp = *queue;
		while (temp && temp->next)
			temp = temp->next;
		temp->next = new;
	}

	return (new);
}


/**
 * BTQA - Advance queue deleting
 * @queue: pointer
 */
void BTQA(bt_node_queue_t **queue)
{
	bt_node_queue_t *temp;

	if (!queue || !*queue)
		return;

	temp = *queue;
	*queue = (*queue)->next;
	free(temp);
}


/**
 * BTQC - clear
 * @queue: pointer
 */
void BTQC(bt_node_queue_t **queue)
{
	if (!queue)
		return;

	while (*queue)
		BTQA(queue);
}


/**
 * BTCI - insert leaves
 * @root: pointer
 * @data: pointer
 * Return: pointer
 */
binary_tree_node_t *BTCI(binary_tree_node_t *root, void *data)
{
	binary_tree_node_t *new = NULL;
	bt_node_queue_t *queue = NULL;

	if (!root)
		return (binary_tree_node(NULL, data));

	queue = BTQP(&queue, root);
	if (!queue)
		return (NULL);

	while (queue)
	{
		if (queue->node->left && queue->node->right)
		{
			if (!BTQP(&queue, queue->node->left) || !BTQP(&queue, queue->node->right))
			{
				BTQC(&queue);
				return (NULL);
			}

			BTQA(&queue);
		}
		else
		{
			new = binary_tree_node(queue->node, data);
			if (!new)
				return (NULL);

			if (!queue->node->left)
				queue->node->left = new;
			else
				queue->node->right = new;

			BTQC(&queue);
		}
	}

	return (new);
}


/**
 * minHSU - sift swapped data
 * @new: pointer
 * @data_cmp: pointer
 * Return: pointer
 */
binary_tree_node_t *minHSU(binary_tree_node_t *new,
							int (data_cmp)(void *, void *))
{
	binary_tree_node_t *temp = NULL;
	void *swap;

	if (!data_cmp)
		return (new);

	temp = new;
	while (temp && temp->parent &&
	       data_cmp(temp->data, temp->parent->data) < 0)
	{
		swap = temp->data;
		temp->data = temp->parent->data;
		temp->parent->data = swap;
		temp = temp->parent;
	}

	return (temp);
}


/**
 * heapInsert - inserts a value into MinBH
 * @root: pointer
 * @data_cmp: pointer
 * @data: pointer
 * Return: pointer
 */
binary_tree_node_t *hI(binary_tree_node_t **root,
						int (data_cmp)(void *, void *), void *data)
{
	binary_tree_node_t *new = NULL;

	if (!root || !data_cmp || !data)
		return (NULL);

	new = BTCI(*root, data);
	if (!new)
		return (NULL);
	if (!*root)
		*root = new;

	new = minHSU(new, data_cmp);

	return (new);
}


/**
 * heap_insert - entry
 * @heap: pointer
 * @data: pointer
 * Return: pointer
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new = NULL;

	if (!heap || !data)
		return (NULL);

	new = hI(&(heap->root), heap->data_cmp, data);
	if (new)
		heap->size++;

	return (new);
}
