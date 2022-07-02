#include "rb_trees.h"
#include <stdlib.h>

/**
* rb_tree_node - red black tree node
* @parent: node
* @value: value
* @color: node color
* Return: node or NULL
*/
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *newnode;

	newnode = malloc(sizeof(rb_tree_t));
	if (newnode)
	{
		newnode->n = value;
		newnode->color = color;
		newnode->parent = parent;
		newnode->left = NULL;
		newnode->righht = NULL;
	}
	else
	{
		newnode = NULL;
	}
	return (newnode);
}
