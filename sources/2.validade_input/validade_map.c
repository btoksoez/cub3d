#include "../../includes/cub3d.h"

// at the end add a 0 in the left of the map
// at the end add multiple 1's in the right and bottom of the map
// check for an empy space on the right (potentially left too)
// map split triggers if there is text after map
// trim 1's which are outside of the outer wall

void	validate_map(t_map *map)
{
	if (invalid_color(map))
		free_map(map, "Invalid color", 1);
	if (map_split(map))
		free_map(map, "Map is separated by empty lines", 1);
	if (invalid_characters(map))
		free_map(map, "Map has invalid characters", 1);
	if (!surrounded_by_walls(map))
		free_map(map, "Map isn't surrounded by walls", 1);
	if (!leaking_empty_spaces(map))
		free_map(map, "Map has empty spaces not surrounded by walls", 1);
}

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
