#include "graphs.h"
#include <stdlib.h>

/**
 * graph_create -  create graph
 * Return: pointer
 */
graph_t *graph_create(void)
{
	graph_t *graph = NULL;

	graph = malloc(sizeof(graph_t));
	if (!graph)
		return (NULL);

	graph->nb_vertices = 0;
	graph->vertices = NULL;

	return (graph);
}
