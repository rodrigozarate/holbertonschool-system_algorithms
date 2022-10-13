#include "pathfinding.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


/**
  * cmpWeights - Guess what, it compares weights
  * @param1: void * pointer castable to dijkstra_vertex
  * @param2: void * pointer castable to dijkstra_vertex
  * Return: 1 if param1 , -1 if param2, 0 if equall
  */
int cmpWeights(const void *param1, const void *param2)
{
	dijkstra_vertex_t *D_vert1 = NULL, *D_vert2 = NULL;

	if (!param1 && !param2)
		return (0);
	if (param1 && !param2)
		return (1);
	if (!param1 && param2)
		return (-1);

	D_vert1 = (dijkstra_vertex_t *)param1;
	D_vert2 = (dijkstra_vertex_t *)param2;

	if (D_vert1->cmlW > D_vert2->cmlW)
		return (1);
	else if (D_vert1->cmlW < D_vert2->cmlW)
		return (-1);
	else if (param1 > param2)
		return (1);
	else if (param1 < param2)
		return (-1);

	return (0);
}

/**
  * pathDjkQueue - seek path over priority queue
  * @dPQ: finished Dijkstra priority queue
  * @tIndex: index of target vertex in priority queue
  * Return: queue or NULL on failure
  */
queue_t *pathDjkQueue(dijkstra_vertex_t *dPQ,
			       size_t tIndex)
{
	queue_t *path = NULL;
	vertex_t *vTX = NULL;
	char *pName = NULL;
	long int i;

	if (!dPQ)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);

	pName = strdup(dPQ[tIndex].vertex->content);
	queue_push_front(path, (void *)pName);
	vTX = dPQ[tIndex].path_vTX;

	for (i = tIndex; i >= 0; i--)
	{
		if (dPQ[i].vertex == vTX)
		{
			pName = strdup(dPQ[i].vertex->content);
			queue_push_front(path, (void *)pName);
			vTX = dPQ[i].path_vTX;
		}
	}

	if (vTX != NULL)
	{
		while (path->front)
			free(dequeue(path));
		queue_delete(path);
		path = NULL;
	}

	return (path);
}

/**
  * checkEdge - finds optimal previous vertex for each edge
  * @dPQ: array of structs Priority Queue
  * @nb_vertices: total amount of vertices
  * @dq_head_i: index in dPQ
  */
void checkEdge(dijkstra_vertex_t *dPQ, size_t nb_vertices,
		 size_t dq_head_i)
{
	dijkstra_vertex_t dq_head;
	edge_t *temp_e = NULL;
	size_t i;

	if (!dPQ)
		return;

	dq_head = dPQ[dq_head_i];

	for (temp_e = dq_head.vertex->edges; temp_e; temp_e = temp_e->next)
	{
		if (dq_head.path_vTX && strcmp(temp_e->dest->content,
					       dq_head.path_vTX->content) == 0)
			continue;

		for (i = dq_head_i; i < nb_vertices; i++)
		{
			if (strcmp(temp_e->dest->content,
				   dPQ[i].vertex->content) == 0)
			{
				if (dq_head.cmlW + temp_e->weight <
				    dPQ[i].cmlW)
				{
					dPQ[i].cmlW =
						dq_head.cmlW +
						temp_e->weight;

					dPQ[i].path_vTX = dq_head.vertex;
				}
			}
		}
	}

	dq_head_i++;

	qsort((void *)(dPQ + dq_head_i), nb_vertices - dq_head_i,
	      sizeof(dijkstra_vertex_t), cmpWeights);
}


/**
  * updateArrGraph - updates array-based priority
  * @dPQ: array of structs
  * @nb_vertices: amount of vertices
  * @start: pointer to starting vertex
  * @target: pointer to target vertex
  * @dq_head_i: index in dPQ that marks the current priority queue
  * @tIndex: final index
  * Return: 0 or 1 on error
  */
int updateArrGraph(dijkstra_vertex_t *dPQ, size_t nb_vertices,
		   const vertex_t *start, const vertex_t *target,
		   size_t dq_head_i, size_t *tIndex)
{
	dijkstra_vertex_t dq_head;

	if (!dPQ || !start || !target || !tIndex)
		return (1);

	dq_head = dPQ[dq_head_i];
	printf("Checking %s, distance from %s is %lu\n",
	       dq_head.vertex->content, start->content, dq_head.cmlW);

	checkEdge(dPQ, nb_vertices, dq_head_i);

	if (strcmp(target->content, dq_head.vertex->content) == 0)
	{
		*tIndex = dq_head_i;
		return (0);
	}

	/* no more to assess */
	if (dq_head_i == nb_vertices - 1)
		return (1);

	/* no more vTXble paths remain */
	if (dPQ[dq_head_i + 1].cmlW == ULONG_MAX ||
	    dPQ[dq_head_i + 1].path_vTX == NULL)
		return (1);

	return (updateArrGraph(dPQ, nb_vertices, start, target,
			     dq_head_i + 1, tIndex));
}


/**
  * dijkstra_graph - searches for target point in a graph using edge weights
  * @graph: pointer to the graph to traverse
  * @start: pointer to starting vertex
  * @target: pointer to target vertex
  * Return: queue or NULL
  */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target)
{
	dijkstra_vertex_t *dijkstra_queue = NULL;
	vertex_t *temp_v = NULL;
	size_t i, tIndex;
	queue_t *path = NULL;

	if (!graph || !graph->nb_vertices || !graph->vertices ||
	    !start || !target)
		return (NULL);

	dijkstra_queue = malloc(sizeof(dijkstra_vertex_t) * graph->nb_vertices);
	if (!dijkstra_queue)
		return (NULL);

	for (i = 0, temp_v = graph->vertices; i < graph->nb_vertices;
	     i++, temp_v = temp_v->next)
	{
		dijkstra_queue[i].vertex = temp_v;

		if (strcmp(start->content, temp_v->content) == 0)
			dijkstra_queue[i].cmlW = 0;
		else
			dijkstra_queue[i].cmlW = ULONG_MAX;

		dijkstra_queue[i].path_vTX = NULL;
	}

	qsort((void *)dijkstra_queue, graph->nb_vertices,
	      sizeof(dijkstra_vertex_t), cmpWeights);

	if (updateArrGraph(dijkstra_queue, graph->nb_vertices,
			  start, target, 0, &tIndex) != 0)
	{
		free(dijkstra_queue);
		return (NULL);
	}

	path = pathDjkQueue(dijkstra_queue, tIndex);
	free(dijkstra_queue);
	return (path);
}
