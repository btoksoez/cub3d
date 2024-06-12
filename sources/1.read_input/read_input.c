#include "../../includes/cub3d.h"

void	read_input(int argc, char *argv[], t_map *map)
{
	int	fd;

	check_arguments(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_message("Failed to open file");
	read_textures(map, fd);
	read_map(map, fd);
	close(fd);
	validate_map(map);
}

void	read_textures(t_map *map, int fd)
{
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	while (line && *line)
	{
		tmp = line;
		ft_skip_whitespace(&tmp);
		if (ft_strlen(tmp) >= 3 && *tmp == 'N' && *(tmp + 1) == 'O')
			get_texture(tmp, 'N', map);
		else if (ft_strlen(tmp) >= 3 && *tmp == 'S' && *(tmp + 1) == 'O')
			get_texture(tmp, 'S', map);
		else if (ft_strlen(tmp) >= 3 && *tmp == 'W' && *(tmp + 1) == 'E')
			get_texture(tmp, 'W', map);
		else if (ft_strlen(tmp) >= 3 && *tmp == 'E' && *(tmp + 1) == 'A')
			get_texture(tmp, 'E', map);
		else if (*tmp == 'F' && ft_strchr(WHITESPACE, *(tmp + 1)))
			get_color(tmp, 'F', map);
		else if (*tmp == 'C' && ft_strchr(WHITESPACE, *(tmp + 1)))
			get_color(tmp, 'C', map);
		if (line)
			free(line);
		if (assigned_all(map))
			return ;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	if (!assigned_all(map))
		free_map(map, "Missing textures or colors in .cub file", 1);
}

void	fill_with_space(t_map *map)
{
	int		row;
	int		coll;
	char	*temp;

	row = 0;
	while (map->map[row])
	{
		coll = 0;
		while (map->map[row][coll])
			coll++;
		if (coll < map->cols)
		{
			temp = ft_realloc(map->map[row], sizeof(char) * (coll + 1),
					sizeof(char) * (map->cols + 1)); // causing problems
			if (!temp)
				free_map(map, "Failed to allocate memory for row", 1);
			map->map[row] = temp;
			while (coll < map->cols)
				map->map[row][coll++] = ' ';
			map->map[row][coll] = '\0';
		}
		row++;
	}
}

void	read_map(t_map *map, int fd)
{
	char	*line;
	int		row;
	char	**temp;

	row = 0;
	line = get_next_line(fd);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		temp = ft_realloc(map->map, sizeof(char *) * (row + 1), sizeof(char *)
				* (row + 2));
		if (!temp)
		{
			free(line);
			if (map->map)
				free_map(map, "Memory allocation failed", 1);
			error_message("Memory allocation failed");
		}
		map->map = temp;
		map->map[row] = ft_strtrim(line, "\n");
		if (!map->map[row])
		{
			free(line);
			free_map(map, "Memory allocation failed", 1);
		}
		free(line);
		line = get_next_line(fd);
		row++;
	}
	remove_extra_rows(map, row, temp);
}

void	check_arguments(int argc, char *argv[])
{
	if (argc != 2)
		error_message("Invalid number of arguments");
	if (!is_cub(argv[1]))
		error_message("File must be of type .cub");
}

bool	is_cub(char *file)
{
	int	i;

	i = 0;
	while (file[i] && file[i] != '.')
		i++;
	if (ft_strcmp(file + i, ".cub") == 0)
		return (true);
	return (false);
}
