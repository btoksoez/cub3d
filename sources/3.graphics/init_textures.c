#include "../../includes/cub3d.h"

void	init_texture(t_game *game, t_img *texture_img, char *texture)
{
	texture_img->img_ptr = mlx_xpm_file_to_image(game->mlx, texture, &texture_img->width, &texture_img->height);
	if (!texture_img->img_ptr)
	{
		mlx_destroy_window(game->mlx, game->win);
		// mlx_destroy_display(game->mlx);
		free(game->mlx);
		if (ft_strcmp(texture, game->map->no_texture) == 0)
			free_map(game->map, "Failed to initialize north texture", 1);
		else if (ft_strcmp(texture, game->map->so_texture) == 0)
			free_map(game->map, "Failed to initialize south texture", 1);
		else if (ft_strcmp(texture, game->map->ea_texture) == 0)
			free_map(game->map, "Failed to initialize east texture", 1);
		else if (ft_strcmp(texture, game->map->we_texture) == 0)
			free_map(game->map, "Failed to initialize west texture", 1);
	}
	texture_img->pixels_ptr = mlx_get_data_addr(texture_img->img_ptr,
												&texture_img->bits_per_pixel,
												&texture_img->line_len,
												&texture_img->endian);
}

void	init_textures(t_game *game, t_textures *textures)
{
	init_texture(game, &textures->north, game->map->no_texture);
	init_texture(game, &textures->south, game->map->so_texture);
	init_texture(game, &textures->east, game->map->ea_texture);
	init_texture(game, &textures->west, game->map->we_texture);
	game->textures = textures;
}
