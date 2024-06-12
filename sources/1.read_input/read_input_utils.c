/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:09:36 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 16:10:40 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_texture_or_color(char *tmp, t_map *map)
{
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
