#include "graphs.h"
#include <stdlib.h>
#include <string.h>


/**
 * graph_add_single_edge - adds a single edge
 * @src: node
 * @dest: node
 * Return: pointer
 */
edge_t *graph_add_single_edge(vertex_t *src, vertex_t *dest)
{
	edge_t *new = NULL, *temp = NULL;

	if (!src || !dest)
		return (NULL);
	new = malloc(sizeof(edge_t));
	if (!new)
		return (NULL);
	new->dest = dest;
	new->next = NULL;
	temp = src->edges;
	while (temp && temp->next)
		temp = temp->next;

	if (temp)
		temp->next = new;
	else
		src->edges = new;
	src->nb_edges++;

	return (new);
}


/**
 * graph_add_edge - adds an edge between two vertices
 * @graph: pointer
 * @src: string
 * @dest: string
 * @type: type of edge
 * Return: 1, 0
 */
int graph_add_edge(graph_t *graph, const char *src,
		   const char *dest, edge_type_t type)
{
	vertex_t *temp_v = NULL, *src_v = NULL, *dest_v = NULL;

	if (!graph || !src || !dest ||
	    type < UNIDIRECTIONAL || type > BIDIRECTIONAL)
		return (0);

	for (temp_v = graph->vertices; temp_v; temp_v = temp_v->next)
	{
		if (strcmp(temp_v->content, src) == 0)
			src_v = temp_v;
		else if (strcmp(temp_v->content, dest) == 0)
			dest_v = temp_v;
	}

	if (!src_v || !dest_v)
		return (0);

	if (graph_add_single_edge(src_v, dest_v) == NULL)
		return (0);

	if (type == BIDIRECTIONAL)
	{
		if (graph_add_single_edge(dest_v, src_v) == NULL)
			return (0);
	}

	return (1);
}
