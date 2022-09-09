#ifndef _HEAP_HLBT_
#define _HEAP_HLBT_

#include <stddef.h>

/**
 * struct binary_tree_node_s - Binary tree node data structure
 *
 * @data: Data stored in a node
 * @left: Pointer to the left child
 * @right: Pointer to the right child
 * @parent: Pointer to the parent node
 */
typedef struct binary_tree_node_s
{
	void *data;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
} binary_tree_node_t;

/**
 * struct heap_s - Heap data structure
 *
 * @size: Size of the heap (number of nodes)
 * @data_cmp: Function to compare two nodes data
 * @root: Pointer to the root node of the heap
 */
typedef struct heap_s
{
	size_t size;
	int (*data_cmp)(void *, void *);
	binary_tree_node_t *root;
} heap_t;

/**
 * struct binary_tree_node_queue_s - Bynari structure
 * @node: node
 * @next: pointer
 */
typedef struct binary_tree_node_queue_s
{
	binary_tree_node_t *node;
	struct binary_tree_node_queue_s *next;
} bt_node_queue_t;

heap_t *heap_create(int (*data_cmp)(void *, void *));
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);


bt_node_queue_t *BTQP(bt_node_queue_t **queue, binary_tree_node_t *node);
void BTQA(bt_node_queue_t **queue);
void BTQC(bt_node_queue_t **queue);
binary_tree_node_t *BTCI(binary_tree_node_t *root, void *data);
binary_tree_node_t *minHSU(binary_tree_node_t *new,
							int (data_cmp)(void *, void *));
binary_tree_node_t *hI(binary_tree_node_t **root,
						int (data_cmp)(void *, void *), void *data);
binary_tree_node_t *heap_insert(heap_t *heap, void *data);

void *heap_extract(heap_t *heap);
void *hE(binary_tree_node_t **root, int (data_cmp)(void *, void *));
void minHSD(binary_tree_node_t *root, int (data_cmp)(void *, void *));
binary_tree_node_t *lILO(binary_tree_node_t *root);
int bTIC(const binary_tree_node_t *tree, size_t node_i, size_t tree_sz);
size_t bTS(const binary_tree_node_t *tree);

void bTD(binary_tree_node_t *tree, void (*free_data)(void *));
void heap_delete(heap_t *heap, void (*free_data)(void *);

#endif
