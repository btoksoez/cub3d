/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btoksoez <btoksoez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:44:47 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/17 10:38:35 by btoksoez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes_normal/cub3d.h"

int	get_texture(char *line, char type, t_map *map)
{
	char	*file;
	char	*line_before;

	line_before = line;
	line += 2;
	ft_skip_whitespace(&line);
	file = ft_strdup_delimiter(line, WHITESPACE);
	if (access(file, F_OK) != 0 || access(file, R_OK) != 0)
	{
		free(file);
		return (false);
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
	return (true);
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

int	get_color(char *line, char type, t_map *map)
{
	char	*num;
	char	*num_trimmed;
	int		i;

	i = 0;
	line++;
	ft_skip_whitespace(&line);
	while (i < 3)
	{
		num = ft_strdup_delimiter(line, ",\n");
		printf("num: %s\n", num);
		num_trimmed = ft_strtrim(num, " ");
		printf("trimmed: %s\n", num_trimmed);
		free(num);
		// if (!ft_isdigit_str(num_trimmed) || ft_strlen(num_trimmed) > 3)
		// {
		// 	free(num_trimmed);
		// 	return (false);
		// }
		assign_color(i, num_trimmed, type, map);
		line += ft_strlen(num_trimmed) + 1;
		free(num_trimmed);
		i++;
	}
	return (true);
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
