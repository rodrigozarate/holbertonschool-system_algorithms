#include "graphs.h"
#include <stdlib.h>
#include <string.h>

/**
 * graph_add_vertex - add vertex to graph
 * @graph: pointer
 * @str: String to store
 * Return: pointer
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *temp = NULL, *tail = NULL, *new = NULL;
	size_t i, str_len;
	char *str_cpy = NULL;

	if (graph == NULL || str == NULL)
		return (NULL);
	for (i = 0, temp = graph->vertices; i < graph->nb_vertices; i++)
	{
		if (!temp || strcmp(temp->content, str) == 0)
			return (NULL);
		if (i == graph->nb_vertices - 1 && !temp->next)
			tail = temp;
		temp = temp->next;
	}

	new = malloc(sizeof(vertex_t));
	if (!new)
		return (NULL);
	str_len = strlen(str);
	str_cpy = malloc(sizeof(char) * str_len + 1);
	if (!str_cpy)
	{
		free(new);
		return (NULL);
	}
	str_cpy = strcpy(str_cpy, str);
	new->index    = i;
	new->content  = str_cpy;
	new->nb_edges = 0;
	new->edges    = NULL;
	new->next     = NULL;
	if (tail)
		tail->next = new;
	else
		graph->vertices = new;
	graph->nb_vertices++;
	return (new);
}
