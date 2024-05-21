#include "../includes/cub3d.h"

void	error_message(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(str, 2);
	exit (1);
}

void	get_texture(char *line, char type, t_map *map)
{
	char *file;

	line += 2;
	skip_whitespace(&line);
	file = ft_strdup_delimiter(line, WHITESPACE);
	if (access(file, F_OK) != 0 || access(file, R_OK) != 0)
	{
		free(file);
		error_message("texture file not readable\n");
	}
	if (type == 'N')
		map->no_texture = file;
	else if (type == 'S')
		map->so_texture = file;
	else if (type == 'W')
		map->we_texture = file;
	else if (type == 'E')
		map->ea_texture = file;
	line += ft_strlen(file);
}
void	assign_color(int i, char *num, char type, t_map *map)
{
	if (i == 0 && type == 'F')
		map->f_color.red = ft_atoi(num);
	else if (i == 1 && type == 'F')
		map->f_color.green = ft_atoi(num);
	else if (i == 2 && type == 'F')
		map->f_color.blue = ft_atoi(num);
	else if (i == 0 && type == 'C')
		map->c_color.red = ft_atoi(num);
	else if (i == 1 && type == 'C')
		map->c_color.green = ft_atoi(num);
	else if (i == 2 && type == 'C')
		map->c_color.blue = ft_atoi(num);
}

void	get_color(char *line, char type, t_map *map)
{
	char	*num;
	int		i;

	i = 0;
	line++;
	skip_whitespace(&line);
	while (i < 3)
	{
		num = ft_strdup_delimiter(line, WS_COMMA);
		if (!ft_isdigit_str(num))
		{
			free(num);
			error_message("Invalid color\n");
		}
		assign_color(i, num, type, map);
		line += ft_strlen(num) + 1;
		free(num);
		i++;
	}
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

bool	assigned_all(t_map *map)
{
	if (map->ea_texture && map->no_texture
		&& map->so_texture && map->we_texture
		&& map->f_color.blue != -1 && map->f_color.green != -1
		&& map->f_color.red != -1 && map->c_color.green != -1
		&& map->c_color.blue != -1 && map->f_color.red != -1
		)
		return (true);
	return (false);
}

void	read_textures(t_map *map, int fd)
{
	char *line;
	char *tmp;

	line = get_next_line(fd);
	while (line)
	{
		tmp = line;
		skip_whitespace(&tmp);
		if (*tmp == 'N' && *(tmp + 1) == 'O')
			get_texture(tmp, 'N', map);
		else if (*tmp == 'S' && *(tmp + 1) == 'O')
			get_texture(tmp, 'S', map);
		else if (*tmp == 'W' && *(tmp + 1) == 'E')
			get_texture(tmp, 'W', map);
		else if (*tmp == 'E' && *(tmp + 1) == 'A')
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
	if (!assigned_all(map))
		error_message("Missing textures or colors in .cub file\n");
}

bool	is_valid_color(int color)
{
	if (color >= 0 && color <= 255)
		return (true);
	return (false);
}

void	validate_map(t_map *map)
{
	if (!is_valid_color(map->f_color.blue) || !is_valid_color(map->f_color.green)
		|| !is_valid_color(map->f_color.red) || !is_valid_color(map->c_color.green)
		|| !is_valid_color(map->c_color.blue) || !is_valid_color(map->c_color.red))
		error_message("Invalid color\n");
}

void	read_input(int argc, char *argv[], t_map *map)
{
	int		fd;

	if (argc != 2)
		error_message("Invalid number of arguments\n");

	if (!is_cub(argv[1]))
		error_message("File must be of type .cub\n");

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_message("Failed to open file\n");

	init_map(map);
	read_textures(map, fd);
	print_map(map);
	// read_map(map, fd, 0);
	// close(fd);
	validate_map(map);

	//check map
		//check for right chars
		//surrounded by walls
}
