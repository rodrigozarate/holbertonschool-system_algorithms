#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include <stddef.h>

/**
 * enum rb_color_e - Possible color of a Red-Black tree
 *
 * @RED: 0 -> Red node
 * @BLACK: 1 -> Black node
 * @DOUBLE_BLACK: 2 -> Null
 */
typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;

/**
 * struct rb_tree_s - Red-Black tree node structure
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 * @color: Color of the node (RED or BLACK)
 */
typedef struct rb_tree_s
{
	int n;
	rb_color_t color;
	struct rb_tree_s *parent;
	struct rb_tree_s *left;
	struct rb_tree_s *right;
} rb_tree_t;

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);

size_t BiggerSizeT(size_t w, size_t h);
size_t TreeHeight(const rb_tree_t *tree);
int ColorTest(const rb_tree_t *tree);
int BinarySearchTree(const rb_tree_t *tree, int *node);
int rb_tree_is_valid(const rb_tree_t *tree);

rb_tree_t *rb_tree_get_uncle(rb_tree_t *n);
rb_tree_t *rb_tree_rotate_left(rb_tree_t *tree);
rb_tree_t *rb_tree_rotate_right(rb_tree_t *tree);
rb_tree_t *rb_tree_insert_case4(rb_tree_t *node);
rb_tree_t *rb_tree_insert_repair(rb_tree_t *root, rb_tree_t *node);
rb_tree_t *rb_tree_insert_recurse(rb_tree_t *tree, int value);
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);

rb_tree_t *array_to_rb_tree(int *array, size_t size);

#endif /* _RB_TREE_H_ */
