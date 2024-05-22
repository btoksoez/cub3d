#include "../includes/cub3d.h"

bool	valid_color(int color)
{
	if (color >= 0 && color <= 255)
		return (true);
	return (false);
}

bool	invalid_color(t_map *map)
{
	if (!valid_color(map->f_color.blue) || !valid_color(map->f_color.green)
		|| !valid_color(map->f_color.red) || !valid_color(map->c_color.green)
		|| !valid_color(map->c_color.blue) || !valid_color(map->c_color.red))
		return (true);
	return (false);
}

bool	map_split(t_map *map)
{
	int	rows;
	int	coll;

	rows = 0;
	while (rows < map->rows)
	{
		coll = 0;
		if (ft_strchr(WHITESPACE, map->map[rows][coll]))
		{
			while (map->map[rows][coll])
			{
				if (!ft_strchr(WHITESPACE, map->map[rows][coll]))
					break ;
				coll++;
			}
			if (map->map[rows][coll] == '\0')
				return (true);
		}
		if (*map->map[rows] == '\0')
			return (true);
		rows++;
	}
	return (false);
}

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

void	validate_map(t_map *map)
{
	if (invalid_color(map))
		free_map(map, "Invalid color", 1);
	if (map_split(map))										// triggers if there is text after
		free_map(map, "Map is separated by empty lines", 1);
	if (invalid_characters(map))
		free_map(map, "Map has invalid characters", 1);
	if (!surrounded_by_walls(map))
		free_map(map, "Map isn't surrounded by walls", 1);

	// check if there is no space without walls surrounding it in the middle of the map
}

// at the end add a 0 in the right and bottom of the map
// at the end add two 1's in the right and bottom of the map
	// printf("%d\n", map->rows);
	// printf("%d\n", map->max_coll);

//check for an empy space on the right (potentially left too)

// 	        11111111111 1111111111111
//         10000000001 1000000000001
//         10110000011 1000000000001
//         1001000000111000000000001
// 111111111011000001001000000000001
// 100000000011000001110111111111111
// 11110111111111011100000010111
// 111101111111110111010100101  0
// 11000000110101011100000010111
// 10000000000000001100000010001
// 10000000000000001101010010001
// 11000001110101011111011110N01
// 11110111 1110101 101111010001
// 11111111 1111111 111111111111
