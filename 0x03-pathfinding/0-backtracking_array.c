#include "pathfinding.h"
#include <stdlib.h>
#include <stdio.h>


/**
  * isValidStep - validates step
  * @path: queue_t candidate solution
  * @map: double char pointer
  * @visited: double char pointer to visited nodes
  * @rows: int count
  * @cols: int count
  * @step: point_t to check
  * Return: 1 or 0
  */
int isValidStep(queue_t *path, char **map, char **visited, int rows,
		int cols, const point_t *step)
{
	if (!path || !map || !visited || !rows || !cols || !step)
		return (0);

	if (!((step->x >= 0 && step->x < cols) &&
	      (step->y >= 0 && step->y < rows)))
		return (0);

	if (map[step->y][step->x] == '1')
		return (0);

	if (visited[step->y][step->x])
		return (0);

	return (1);
}


/**
  * addPointToPath - adds a point to map
  * @path: queue_t candidate solution
  * @curr: const pointer
  * Return: 1 or 0
  */
int addPointToPath(queue_t *path, const point_t *curr)
{
	point_t *new = NULL;

	if (!path || !curr)
		return (0);

	new = malloc(sizeof(point_t));
	if (!new)
		return (0);

	new->x = curr->x;
	new->y = curr->y;

	if (!queue_push_front(path, (void *)new))
	{
		free(new);
		return (0);
	}

	return (1);
}


/**
  * floodFillMaze - backtrack_array
  * @path: queue_t candidate solution
  * @map: double char pointer
  * @visited: double char pointer to visited nodes
  * @rows: int count
  * @cols: int count
  * @curr: const point_t pointer
  * @target: const point_t pointer
  * Return: 1 or 0
  */
int floodFillMaze(queue_t *path, char **map, char **visited, int rows,
		  int cols, const point_t *curr, const point_t *target)
{
	point_t next_step[4] = { {+1, 0}, {0, +1}, {-1, 0}, {0, -1} };
	int i, target_found = 0;

	if (!path || !map || !visited || !rows || !cols || !curr || !target)
		return (0);

	for (i = 0; i < 4; i++)
	{
		next_step[i].x += curr->x;
		next_step[i].y += curr->y;
	}
	printf("Checking coordinates [%i, %i]\n", curr->x, curr->y);
	visited[curr->y][curr->x] = 1;

	if (curr->x == target->x && curr->y == target->y)
		return (addPointToPath(path, curr));

	for (i = 0; !target_found && i < 4; i++)
	{
		if (isValidStep(path, map, visited, rows, cols, next_step + i))
		{
			target_found |= floodFillMaze(path, map, visited,
						      rows, cols,
						      next_step + i, target);
		}
	}

	if (target_found)
		return (addPointToPath(path, curr));

	return (0);
}


/**
  * backtracking_array -  searches path
  * @map: double char pointer
  * @rows: int count
  * @cols: int count
  * @start: const point_t pointer
  * @target: const point_t pointer
  * Return: rqueue or NULL
  */
queue_t *backtracking_array(char **map, int rows, int cols,
			    point_t const *start, point_t const *target)
{
	queue_t *path = NULL;
	char **visited = NULL;
	int i, j;

	if (!map || !rows || !cols || !start || !target)
		return (NULL);

	path = queue_create();
	if (!path)
		return (NULL);
	visited = malloc(sizeof(char *) * rows);
	if (!visited)
	{
		free(path);
		return (NULL);
	}
	for (i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(char));
		if (!visited[i])
		{
			for (j = 0; j < i; j++)
				free(visited[i]);
			free(visited);
			free(path);
			return (NULL);
		}
	}
	if (!floodFillMaze(path, map, visited, rows, cols, start, target))
	{
		while (path->front)
			free(dequeue(path));
		queue_delete(path);
		path = NULL;
	}

	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);
	return (path);
}
