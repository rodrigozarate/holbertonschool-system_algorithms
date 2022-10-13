#include "pathfinding.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
  * dejavuVTX - checks for matching vertex
  * @path: queue to search
  * @vertex: vertex containing data to search for
  * Return: matching queue node or NULL
  */
queue_node_t *dejavuVTX(queue_t *path, const vertex_t *vertex)
{
	queue_node_t *temp = NULL;
	char *vertex_content = NULL;

	if (!path || !path->front || !path->back || !vertex)
		return (NULL);

	temp = path->front;
	while (temp)
	{
		if (temp->ptr)
		{
			vertex_content = (char *)temp->ptr;

			if (strcmp(vertex->content, vertex_content) == 0)
				return (temp);
		}

		temp = temp->next;
	}

	return (NULL);
}

/**
  * backtrackPath - Keep track clean
  * @path: queue of visited node content backtracking candidate
  * @lastSplit: last known split
  */
void backtrackPath(queue_t *path, const vertex_t *lastSplit)
{
	queue_node_t *node = NULL;
	char *vertex_content = NULL;

	if (!path || !path->front || !path->back || !lastSplit)
		return;

	node = path->back;
	if (node)
		vertex_content = (char *)node->ptr;

	while (node && vertex_content &&
	       strcmp(vertex_content, lastSplit->content) != 0)
	{
		if (node && node->prev)
			node->prev->next = NULL;
		path->back = node->prev;
		if (path->back == NULL)
			path->front = NULL;

		free(node);
		free(vertex_content);

		node = path->back;
		if (node)
			vertex_content = (char *)node->ptr;
	}
}

/**
  * graphDFS - recursive Depth-First-Search
  * @path: current candidate solution
  * @curr: current vertex in graph
  * @target: target vertex in graph
  * Return: 1 or 0
  */
int graphDFS(queue_t *path, const vertex_t *curr, const vertex_t *target)
{
	char *content_copy = NULL;
	int target_found = 0;
	edge_t *temp_e = NULL;

	if (!path || !curr || !target)
		return (0);

	printf("Checking %s\n", curr->content);

	content_copy = strdup(curr->content);
	if (!content_copy)
	{
		perror("graphDFS: strdup");
		return (0);
	}
	if (!queue_push_back(path, (void *)content_copy))
	{
		free(content_copy);
		return (0);
	}

	if (strcmp(curr->content, target->content) == 0)
		return (1);

	for (temp_e = curr->edges; !target_found && temp_e;
	     temp_e = temp_e->next)
	{
		if (!dejavuVTX(path, temp_e->dest))
		{
			target_found |= graphDFS(path, temp_e->dest, target);

			if (!target_found)
				backtrackPath(path, curr);
		}
	}

	return (target_found);
}


/**
  * backtracking_graph - searches a target point in a graph
  * @graph: pointer to the graph to traverse
  * @start: pointer to starting vertex
  * @target: pointer to target vertex
  * Return: queue or NULL
  */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target)
{
	queue_t *path = NULL;

	if (!graph || !graph->nb_vertices || !graph->vertices ||
	    !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	if (!graphDFS(path, start, target))
	{
		while (path->front)
			free(dequeue(path));
		queue_delete(path);
		return (NULL);
	}

	return (path);
}
