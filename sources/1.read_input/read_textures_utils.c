#include "../../includes/cub3d.h"

void	get_texture(char *line, char type, t_map *map)
{
	char	*file;

	line += 2;
	ft_skip_whitespace(&line);
	file = ft_strdup_delimiter(line, WHITESPACE);
	if (access(file, F_OK) != 0 || access(file, R_OK) != 0)
	{
		free(file);
		free(line);
		free_map(map, "texture file not readable", 1);
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
	ft_skip_whitespace(&line);
	while (i < 3)
	{
		num = ft_strdup_delimiter(line, WS_COMMA);
		if (!ft_isdigit_str(num))
		{
			free(num);
			free(line);
			free_map(map, "invalid color", 1);
		}
		assign_color(i, num, type, map);
		line += ft_strlen(num) + 1;
		free(num);
		i++;
	}
}

bool	assigned_all(t_map *map)
{
	if (map->ea_texture && map->no_texture && map->so_texture && map->we_texture
		&& map->f_color.blue != -1 && map->f_color.green != -1
		&& map->f_color.red != -1 && map->c_color.green != -1
		&& map->c_color.blue != -1 && map->f_color.red != -1)
		return (true);
	return (false);
}
