/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:49:26 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/13 12:22:09 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	error_message(t_map *map, char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	free_enemies(map);
	exit(1);
}

int	close_window(t_game *game, int status, int exit)
{
	if (exit == WON)
		clean_up(game, "You Won!", status);
	else
		clean_up(game, "Game Over!", status);
	return (0);
}

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
		error_message(map, str);
}

void	free_textures(t_game *game, t_textures *textures)
{
	int	i;
	int	j;

	if (textures->north.img_ptr)
		mlx_destroy_image(game->mlx, textures->north.img_ptr);
	if (textures->west.img_ptr)
		mlx_destroy_image(game->mlx, textures->west.img_ptr);
	if (textures->south.img_ptr)
		mlx_destroy_image(game->mlx, textures->south.img_ptr);
	if (textures->east.img_ptr)
		mlx_destroy_image(game->mlx, textures->east.img_ptr);
	if (textures->aim.img_ptr)
		mlx_destroy_image(game->mlx, textures->aim.img_ptr);
	if (textures->map.img_ptr)
		mlx_destroy_image(game->mlx, textures->map.img_ptr);
	if (textures->ground.img_ptr)
		mlx_destroy_image(game->mlx, textures->ground.img_ptr);
	if (textures->sky.img_ptr)
		mlx_destroy_image(game->mlx, textures->sky.img_ptr);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 5)
		{
			if (textures->weapon[i][j].img_ptr)
				mlx_destroy_image(game->mlx, textures->weapon[i][j].img_ptr);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 4)
		{
			if (textures->enemy[i][j].img_ptr)
				mlx_destroy_image(game->mlx, textures->enemy[i][j].img_ptr);
			j++;
		}
		i++;
	}
}

void	free_enemies(t_map *map)
{
	int	i;

	i = 0;
	if (!map->enemies)
		return ;
	while (i < map->enemy_count)
	{
		free(map->enemies[i++]);
	}
	free(map->enemies);
}

void	clean_up(t_game *game, char *str, int status)
{
	free_textures(game, game->textures);
	free_map(game->map, NULL, 0);
	mlx_destroy_image(game->mlx, game->img.img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	// mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (status)
		error_message(game->map, str);
	else
	{
		free_enemies(game->map);
		ft_printf("%s\n", str);
		exit(0);
	}
}
