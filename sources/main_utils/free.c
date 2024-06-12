/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:14:18 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 17:14:39 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map_copy(char **map)
{
	int	rows;

	rows = 0;
	if (map)
	{
		while (map[rows])
		{
			free(map[rows]);
			rows++;
		}
		free(map);
	}
}

void	free_map(t_map *map, char *str, int status)
{
	int	rows;

	rows = 0;
	if (map->map)
	{
		while (map->map[rows])
		{
			free(map->map[rows]);
			rows++;
		}
		free(map->map);
	}
	free(map->ea_texture);
	free(map->no_texture);
	free(map->we_texture);
	free(map->so_texture);
	if (status == 1)
		error_message(str);
}

void	free_textures(t_game *game, t_textures *textures)
{
	if (textures->north.img_ptr)
		mlx_destroy_image(game->mlx, textures->north.img_ptr);
	if (textures->west.img_ptr)
		mlx_destroy_image(game->mlx, textures->west.img_ptr);
	if (textures->south.img_ptr)
		mlx_destroy_image(game->mlx, textures->south.img_ptr);
	if (textures->east.img_ptr)
		mlx_destroy_image(game->mlx, textures->east.img_ptr);
}
