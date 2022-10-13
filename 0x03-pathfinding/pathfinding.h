#ifndef HOLBI_PATHFINDING
#define HOLBI_PATHFINDING

#include "queues.h"
#include "graphs.h"

/**
 * struct point_s - X Y coordinates
 *
 * @x: X
 * @y: Y
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;

/**
 * struct dijkstra_vertex_s - dijkstra vertex struct
 * @vertex: vertex
 * @cmlW: weight
 * @path_vTX: verified path vertex
 */
typedef struct dijkstra_vertex_s
{
	vertex_t *vertex;
	size_t cmlW;
	vertex_t *path_vTX;
} dijkstra_vertex_t;

queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target);

queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
			    vertex_t const *target);

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
			vertex_t const *target);

#endif /* HOLBI_PATHFINDING */
