#include "../../includes/cub3d.h"

bool	surrounded_by_walls(t_map *map)
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
