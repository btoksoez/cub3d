#include "../../includes/cub3d.h"

void	get_player_coordinates(t_map *map, int rows, int coll)
{
	map->player.x = coll;
	map->player.y = rows;
	if (map->map[rows][coll] == 'N')
		map->player_dir = NORTH;
	if (map->map[rows][coll] == 'S')
		map->player_dir = SOUTH;
	if (map->map[rows][coll] == 'E')
		map->player_dir = EAST;
	if (map->map[rows][coll] == 'W')
		map->player_dir = WEST;
	map->map[rows][coll] = '0';
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
				if (player_found)
					free_map(map, "There can only be 1 player", 1);
				get_player_coordinates(map, rows, coll);
				player_found = true;
			}
			if (!ft_strchr(VALID_CHARS, map->map[rows][coll]))
				return (true);
			coll++;
		}
		if (map->cols < coll)
			map->cols = coll;
		rows++;
	}
	if (!player_found)
		free_map(map, "There is no player in this map", 1);
	fill_with_space(map);
	return (false);
}
