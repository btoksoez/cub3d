#include "../../includes/cub3d.h"

void	init_window(t_game *game, t_map *map)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		free_map(map, "Mlx initialization failed", 1);
	game->win = mlx_new_window(game->mlx, game->width, game->height, "cub3D");
	if (!game->win)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_map(map, "Window initialization failed", 1);
	}
}

void	init_image(t_game *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx, game->width, game->height);
	if (game->img.img_ptr == NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_map(game->map, "Image initialization failed", 1);
	}
	game->img.pixels_ptr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bits_per_pixel,
			&game->img.line_len,
			&game->img.endian);
}

void	init_game_images()
{
	//load images from xpm to img pointers
	//store them in pointers?
}

void	init_events(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask,
		&close_window, game);
	mlx_mouse_hook(game->win, mouse_hook, game);
}

void	init_game_struct(t_game *game, t_map *map)
{
	game->width = map->max_coll * SCALE;
	game->height = map->rows * SCALE;
	game->map = map;
	game->player_x = map->player_x * SCALE + (SCALE / 3);
	game->player_y = map->player_y * SCALE + (SCALE / 3);
	game->player_angle = 0;
}

void	init_mlx(t_game *game, t_map *map)
{
	init_game_struct(game, map);
	init_window(game, map);
	init_image(game);
	init_game_images();
	init_events(game);
}


