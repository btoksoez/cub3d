/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:46:18 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/20 10:45:32 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes_bonus/cub3d_bonus.h"

void	read_input(int argc, char *argv[], t_map *map)
{
	check_arguments(map, argc, argv);
	map->fd = open(argv[1], O_RDONLY);
	if (map->fd< 0)
		error_message(map, "Failed to open file");
	read_textures(map);
	read_map(map);
	validate_map(map);
}

void	read_textures(t_map *map)
{
	char	*line;
	char	*tmp;

	line = get_next_line(map->fd);
	while (line && *line)
	{
		tmp = line;
		ft_skip_whitespace(&tmp);
		if (!get_texture_or_color(tmp, map))
		{
			free(line);
			free_map(map, "invalid texture file or color", 1);
		}
		if (line)
			free(line);
		if (assigned_all(map))
			return ;
		line = get_next_line(map->fd);
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
					sizeof(char) * (map->cols + 1));
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

void	read_map_aux(t_map *map, int row, char **temp, char *line)
{
	temp = ft_realloc(map->map, sizeof(char *) * (row + 1), sizeof(char *)
			* (row + 2));
	if (!temp)
	{
		free(line);
		free_map(map, "map allocation failed", 1);
	}
	map->map = temp;
	map->map[row] = ft_strtrim(line, "\n");
	if (!map->map[row])
	{
		free(line);
		free_map(map, "Memory allocation failed", 1);
	}
}

void	read_map(t_map *map)
{
	char	*line;
	int		row;
	char	**temp;

	row = 0;
	temp = NULL;
	line = get_next_line(map->fd);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(map->fd);
	}
	while (line)
	{
		read_map_aux(map, row, temp, line);
		free(line);
		line = get_next_line(map->fd);
		row++;
	}
	remove_extra_rows(map, row, temp);
}
