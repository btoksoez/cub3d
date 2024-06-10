#include "../../includes_bonus/cub3d.h"

bool	flood_fill(t_map *map_array, char **map, int row, int col)
{
	if (row < 0 || col < 0 || row >= map_array->rows || col >= map_array->cols)
		return (false);
	if (map[row][col] == WALL || map[row][col] == VISITED)
		return (true);
	if (map[row][col] == '\0' || map[row][col] == ' ')
		return (false);
	map[row][col] = VISITED;
	if (!flood_fill(map_array, map, row + 1, col))
		return (false);
	if (!flood_fill(map_array, map, row, col + 1))
		return (false);
	if (!flood_fill(map_array, map, row - 1, col))
		return (false);
	if (!flood_fill(map_array, map, row, col - 1))
		return (false);
	return (true);
}

char	**copy_map(t_map *map)
{
	char	**map_copy;
	int		row;

	row = 0;
	map_copy = (char **)malloc(sizeof(char *) * map->rows);
	if (!map_copy)
		error_message("Malloc error copy map\n");
	while (map->map[row])
	{
		map_copy[row] = ft_strdup(map->map[row]);
		row++;
	}
	map_copy[row] = NULL;
	return (map_copy);
}

bool	empty_left(char **map)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == EMPTY)
			{
				return (true);
			}
			col++;
		}
		row++;
	}
	return (false);
}

bool	surrounded_by_walls(t_map *map)
{
	char **map_copy;
	int	row;
	int	col;

	map_copy = copy_map(map);	//copy map and put  V for visited floors, player is 0 too
	row = 0;
	col = 0;
	while (map_copy[row])
	{
		col = 0;
		while (map_copy[row][col])
		{
			if (map_copy[row][col] == EMPTY)
			{
				if (!flood_fill(map, map_copy, row, col))
					return (false);
			}
			col++;
		}
		row++;
	}
	if (empty_left(map_copy))
		return (false);
	return (true);
}


bool	surrounded_by_walls2(t_map *map)
{
	int		row;
	int		coll;
	bool	last_dir;

	row = 0;
	coll = 0;
	last_dir = false;
	while (ft_isspace(map->map[row][coll]))
		coll++;
	if (map->map[row][coll] == EMPTY)
		return (false);
	else if (map->map[row][coll] == WALL)
	{
		if (!valid_upside(map, &coll, &row, &last_dir))
			return (false);
		if (!valid_rightside(map, &coll, &row, &last_dir))
			return (false);
		if (!valid_downside(map, &coll, &row, &last_dir))
			return (false);
		if (!valid_leftside(map, &coll, &row, &last_dir))
			return (false);
	}
	return (true);
}

bool	valid_upside(t_map *map, int *coll, int *row, bool *last_dir)
{
	while (*coll < (map->cols - 1))
	{
		if (*row != 0 && map->map[*row - 1][*coll] == WALL && !*last_dir)
		{
			*last_dir = false;
			(*row)--;
		}
		else if (map->map[*row][*coll + 1] == WALL)
		{
			*last_dir = false;
			(*coll)++;
		}
		else if (map->map[*row][*coll + 1] == EMPTY)
			return (false);
		else if (map->map[*row + 1][*coll] == WALL && map->map[*row][*coll + 1] != EMPTY)
		{
			*last_dir = true;
			(*row)++;
		}
		else
			return (false);
	}
	return (true);
}

bool	valid_rightside(t_map *map, int *coll, int *row, bool *last_dir)
{
	while (*row < (map->rows - 1))
	{
		if (*coll != (map->cols - 1) && map->map[*row][*coll + 1] == WALL && !*last_dir)
		{
			*last_dir = false;
			(*coll)++;
		}
		else if (map->map[*row + 1][*coll] == WALL)
		{
			*last_dir = false;
			(*row)++;
		}
		else if (map->map[*row + 1][*coll] == EMPTY)
			return (false);
		else if (map->map[*row][*coll - 1] == WALL && map->map[*row + 1][*coll] != EMPTY)
		{
			*last_dir = true;
			(*coll)--;
		}
		else
			return (false);
	}
	return (true);
}

bool	valid_downside(t_map *map, int *coll, int *row, bool *last_dir)
{
	while (*coll > 0)
	{
		if (*row != (map->rows - 1) && map->map[*row + 1][*coll] == WALL && !*last_dir)
		{
			*last_dir = false;
			(*row)++;
		}
		else if (map->map[*row][*coll - 1] == WALL)
		{
			*last_dir = false;
			(*coll)--;
		}
		else if (map->map[*row][*coll - 1] == EMPTY)
			return (false);
		else if (map->map[*row - 1][*coll] == WALL && map->map[*row][*coll - 1] != EMPTY)
		{
			*last_dir = true;
			(*row)--;
		}
		else
			return (false);
	}
	if (ft_strchr(map->map[map->rows - 1], '0'))
		return (false);
	return (true);
}

bool	valid_leftside(t_map *map, int *coll, int *row, bool *last_dir)
{
	while (*row > 0)
	{
		if (*coll != 0 && map->map[*row][*coll - 1] == WALL && !*last_dir)
		{
			*last_dir = false;
			(*coll)--;
		}
		else if (map->map[*row - 1][*coll] == WALL)
		{
			*last_dir = false;
			(*row)--;
		}
		else if (map->map[*row - 1][*coll] == EMPTY)
			return (false);
		else if (map->map[*row][*coll + 1] == WALL && map->map[*row - 1][*coll] != EMPTY)
		{
			*last_dir = true;
			(*coll)++;
		}
		else
			return (false);
	}
	return (true);
}
