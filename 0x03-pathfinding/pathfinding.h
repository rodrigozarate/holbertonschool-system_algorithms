#ifndef HOLBI_PATHFINDING
#define HOLBI_PATHFINDING

#include "queues.h"

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

queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target);

#endif /* HOLBI_PATHFINDING */