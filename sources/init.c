#include "../includes/cub3d.h"

void init_map(t_map *map)
{
	if (map == NULL)
		return;
	map->map = NULL;
	map->rows = 0;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->f_color.red = -1;
	map->f_color.green = -1;
	map->f_color.blue = -1;
	map->c_color.red = -1;
	map->c_color.green = -1;
	map->c_color.blue = -1;
}
void	init_game(t_game *game, t_map *map)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_message("MLX init error\n");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
	{
		// mlx_destroy_display(game->mlx);	//add for linux
		free(game->mlx);
		error_message("MLX Window error\n");
	}
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img.img_ptr == NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		// mlx_destroy_display(game->mlx);	//add for linux
		free(game->mlx);
		error_message("MLX IMG error\n");
	}
	game->img.pixels_ptr = mlx_get_data_addr(game->img.img_ptr,
			&game->img.bits_per_pixel,
			&game->img.line_len,
			&game->img.endian);
	game->map = map;
}

void	init_images()
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

void	init(t_game *game, t_map *map)
{
	init_game(game, map);
	init_images();
	init_events(game);
}


