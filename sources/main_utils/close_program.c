#include "../../includes/cub3d.h"

void	error_message(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
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

void	clean_up(t_game *game, char *str, int status)
{
	free_textures(game, game->textures);
	free_map(game->map, NULL, 0);
	mlx_destroy_image(game->mlx, game->img.img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (status)
		error_message(str);
	else
	{
		ft_printf("%s\n", str);
		exit(0);
	}
}
