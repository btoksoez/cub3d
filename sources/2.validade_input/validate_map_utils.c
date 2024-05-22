#include "../../includes/cub3d.h"

void	get_player_coordinates(t_map *map, int rows, int coll)
{
	map->player_x = coll;
	map->player_y = rows;
	if (map->map[rows][coll] == 'N')
		map->player_dir = NORTH;
	if (map->map[rows][coll] == 'S')
		map->player_dir = SOUTH;
	if (map->map[rows][coll] == 'E')
		map->player_dir = EAST;
	if (map->map[rows][coll] == 'W')
		map->player_dir = WEAST;
}

bool	invalid_characters(t_map *map)
{
	int		rows;
	int		coll;
	bool	player_found;

	rows = 0;
	player_found = false;
	while (rows < map->rows)
	{
		coll = 0;
		while (map->map[rows][coll])
		{
			if (ft_strchr(PLAYER, map->map[rows][coll]))
			{
				get_player_coordinates(map, rows, coll);
				player_found = true;
			}
			if (!ft_strchr(VALID_CHARS, map->map[rows][coll]))
				return (true);
			coll++;
		}
		if (map->max_coll < coll)
			map->max_coll = coll;
		rows++;
	}
	if (!player_found)
		free_map(map, "There is no player in this map", 1);
	return (false);
}

bool	found_leaking_space(t_map *map, int row, int coll)
{
	if (row != 0)
	{
		if (map->map[row - 1][coll] != WALL && !ft_isspace(map->map[row - 1][coll]))
			return (true);
	}
	if (row != map->rows - 1)
	{
		if (map->map[row + 1][coll] != WALL && !ft_isspace(map->map[row + 1][coll]))
			return (true);
	}
	if (coll != 0)
	{
		if (map->map[row][coll - 1] != WALL && !ft_isspace(map->map[row][coll - 1]))
			return (true);
	}
	if (coll != map->max_coll - 1)
	{
		if (map->map[row][coll + 1] != WALL && !ft_isspace(map->map[row][coll + 1]))
			return (true);
	}
	return (false);
}

bool	leaking_empty_spaces(t_map *map)
{
	int	row;
	int	coll;

	row = 0;
	while (map->map[row])
	{
		coll = 0;
		while (map->map[row][coll])
		{
			if (ft_isspace(map->map[row][coll]))
				if (found_leaking_space(map, row, coll))
					return (false);
			coll++;
		}
		row++;
	}
	return (true);
}
