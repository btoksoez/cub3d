#include "../includes/cub3d.h"

void	error_message(char *str)
{
	ft_putstr_fd(str, 2);
	exit (1);
}

void	get_texture(char *line, char type)
{
	char *file;

	skip_whitespace(line);
	file = ft_strdup_delimiter(line, WHITESPACE);
	if (access(file, F_OK) != 0 && access(file, R_OK) != 0)
		error_message("texture file not readable\n");
	if (type == 'N')




}

bool	is_cub(char *file)
{
	int	i;

	i = 0;
	while (file[i] && file[i] != ".")
		i++;
	if (ft_strcmp(file + i, ".cub") == 0)
		return (true);
	return (false);
}

void	read_textures(t_map *map, int fd, int rows)
{
	char *line;

	line = get_next_line(fd);
	while (line)
	{
		if (*line == 'N' && *(line + 1) == 'O')
			get_texture(line, 'N', map);
	}
}

void	read_map(t_map *map, int fd, int rows)
{
	char	*line;

	line = get_next_line(fd);
	if (line)
		read_map(map, fd, rows + 1);
	else
	{
		if (rows == 0)
			error_message("Empty file");
		map->map = ft_calloc((rows + 1), sizeof(char *));
		if (!map->map)
			error_message("Memory allocation failed");
		map->rows = rows;
	}
	if (line)
	{
		map->map[rows] = ft_strtrim(line, "\n");
		if (!map->map[rows])
		{
			free(line);
			free_map(map, "Memory allocation failed", 1);
		}
		free(line);
	}
}

bool	read_input(int argc, char *argv[], t_map *map)
{
	int		fd;
	char	*line;

	if (argc != 2)
		error_message("Invalid number of arguments");

	if (!is_cub(argv[1]))
		error_message("File must be of type .cub");

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_message("Failed to open file");

	read_textures(map, fd, 0);
	read_map(map, fd, 0);
	close(fd);
	validade_map(map);


	//check other args
		//check specifier
		//check for file access
		//check for number boundaries

	//check map
		//check for right chars
		//surrounded by walls
}
