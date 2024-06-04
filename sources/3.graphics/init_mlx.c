#include "../../includes/cub3d.h"

void	init_mlx(t_game *game, t_textures *textures, t_player *player, t_map *map)
{
	init_game_struct(game, player, map);
	init_window(game, map);
	init_image(game);
	init_game_images(game, textures);
	init_events(game);
}

int	convert(t_rgb color)
{
	return (color.red << 16 | color.green << 8 | color.blue);
}

void	init_game_struct(t_game *game, t_player *player, t_map *map)
{
	game->width = map->cols * SCALE;
	game->height = map->rows * SCALE;
	game->map = map;
	game->player = player;
	game->dir = 0;
	game->f_color = convert(map->f_color);
	game->c_color = convert(map->c_color);
	player->left_right = 0;
	player->up_down = 0;
	player->rot = 0;
	player->p_angle = map->player_dir;
	player->pos.x = map->player.x * SCALE + 3 * (PSIZE / 2);
	player->pos.y = map->player.y * SCALE + 3 * (PSIZE / 2);
	player->look_dir = 0;
	player->speed = 2;
	player->jump_height = 0;
	player->jumping = false;
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

void	init_game_images(t_game *game, t_textures *textures)
{
	textures->north.img_ptr = mlx_xpm_file_to_image(game->mlx, game->map->no_texture, &textures->north.width, &textures->north.height);
	if (!textures->north.img_ptr)
	{
		mlx_destroy_window(game->mlx, game->win);
		// mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_map(game->map, "Failed to initialize north texture", 1);
	}
	textures->north.pixels_ptr = mlx_get_data_addr(textures->north.img_ptr,
													&textures->north.bits_per_pixel,
													&textures->north.line_len,
													&textures->north.endian);

	textures->south.img_ptr = mlx_xpm_file_to_image(game->mlx, game->map->so_texture, &textures->south.width, &textures->south.height);
	if (!textures->south.img_ptr)
	{
		mlx_destroy_window(game->mlx, game->win);
		// mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_map(game->map, "Failed to initialize south texture", 1);
	}
	textures->south.pixels_ptr = mlx_get_data_addr(textures->south.img_ptr,
													&textures->south.bits_per_pixel,
													&textures->south.line_len,
													&textures->south.endian);

	textures->west.img_ptr = mlx_xpm_file_to_image(game->mlx, game->map->we_texture, &textures->west.width, &textures->west.height);
	if (!textures->west.img_ptr)
	{
		mlx_destroy_window(game->mlx, game->win);
		// mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_map(game->map, "Failed to initialize north texture", 1);
	}
	textures->west.pixels_ptr = mlx_get_data_addr(textures->west.img_ptr,
													&textures->west.bits_per_pixel,
													&textures->west.line_len,
													&textures->west.endian);
	textures->east.img_ptr = mlx_xpm_file_to_image(game->mlx, game->map->ea_texture, &textures->east.width, &textures->east.height);
	if (!textures->east.img_ptr)
	{
		mlx_destroy_window(game->mlx, game->win);
		// mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_map(game->map, "Failed to initialize north texture", 1);
	}
	textures->east.pixels_ptr = mlx_get_data_addr(textures->east.img_ptr,
													&textures->east.bits_per_pixel,
													&textures->east.line_len,
													&textures->east.endian);
	game->textures = textures;
	// print_pixels(game);
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
