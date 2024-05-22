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

void	player_access(t_map *map, char **visited, int x, int y)
{
	if (visited[y][x] == VISITED || visited[y][x] == WALL)
		return ;
	if (ft_strchr(WHITESPACE, visited[y][x]))
		map->valid = false;
	visited[y][x] = VISITED;
	player_access(map, visited, x + 1, y);
	player_access(map, visited, x - 1, y);
	player_access(map, visited, x, y + 1);
	player_access(map, visited, x, y - 1);
}

char	**copy_map(t_map *map, char **original, int rows)
{
	char	**copy;
	int		i;

	copy = ft_calloc(rows + 1, sizeof(char *));
	if (!copy)
		free_map(map, "Memory allocation failed", 1);
	i = 0;
	while (i < rows)
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
		{
			ft_freematrix(copy);
			free_map(map, "Memory allocation failed", 1);
		}
		i++;
	}
	return (copy);
}

bool	surrounded_by_walls(t_map *map)
{
	char	**visited;

	visited = copy_map(map, map->map, map->rows);
	player_access(map, visited, map->player_x, map->player_y);
	if (visited)
		ft_freematrix(visited);
	if (map->valid == true)
		return (true);
	return (false);
}

bool	invalid_characters(t_map *map)
{
	int	rows;
	int	coll;

	rows = 0;
	while (rows < map->rows)
	{
		coll = 0;
		while (map->map[rows][coll])
		{
			if (!ft_strchr(VALID_CHARS, map->map[rows][coll]))
				return (true);
			coll++;
		}
		rows++;
	}
	return (false);
}

void	validate_map(t_map *map)
{
	if (invalid_color(map))
		free_map(map, "Invalid color", 1);
	if (map_split(map))
		free_map(map, "Map is separated by empty lines", 1);
	if (invalid_characters(map))
		free_map(map, "Map has invalid characters", 1);
	// if (!surrounded_by_walls(map))
	// 	free_map(map, "Map isn't surrounded by walls", 1);
}
