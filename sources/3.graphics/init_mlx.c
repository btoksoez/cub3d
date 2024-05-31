#include "../../includes/cub3d.h"

void	init_mlx(t_game *game, t_player *player, t_map *map)
{
	init_game_struct(game, player, map);
	init_window(game, map);
	init_image(game);
	// init_game_images();
	init_events(game);
}

void	init_game_struct(t_game *game, t_player *player, t_map *map)
{
	game->width = map->cols * SCALE;
	game->height = map->rows * SCALE;
	game->map = map;
	game->player = player;
	player->left_right = 0;
	player->up_down = 0;
	player->rot = 0;
	player->p_angle = map->player_dir;
	player->pos.x = map->player.x * SCALE + 3 * (PSIZE / 2);
	player->pos.y = map->player.y * SCALE + 3 * (PSIZE / 2);
	player->look_dir = 0;
}

void	init_window(t_game *game, t_map *map)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		free_map(map, "Mlx initialization failed", 1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->mapwin = mlx_new_window(game->mlx, game->width, game->height, "map");
	if (!game->win)
	{
		// mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_map(map, "Window initialization failed", 1);
	}
}

void	init_image(t_game *game)
{
	game->img.img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->mapimg.img_ptr = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->img.img_ptr)
	{
		mlx_destroy_window(game->mlx, game->win);
		// mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_map(game->map, "Image initialization failed", 1);
	}
	game->img.pixels_ptr = mlx_get_data_addr(game->img.img_ptr,
		&game->img.bits_per_pixel,
		&game->img.line_len,
		&game->img.endian);
	game->mapimg.pixels_ptr = mlx_get_data_addr(game->mapimg.img_ptr,
		&game->mapimg.bits_per_pixel,
		&game->mapimg.line_len,
		&game->mapimg.endian);
}

void	init_game_images()
{
	//load images from xpm to img pointers
	//store them in pointers?
}

void	init_events(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->mapwin, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->mapwin, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &close_window, game);
	mlx_hook(game->mapwin, DestroyNotify, StructureNotifyMask, &close_window, game);
	mlx_mouse_hook(game->win, mouse_hook, game);
	mlx_mouse_hook(game->mapwin, mouse_hook, game);
}
