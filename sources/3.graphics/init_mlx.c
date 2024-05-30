#include "../../includes/cub3d.h"

void	init_mlx(t_game *game, t_player *player, t_map *map)
{
	init_game_struct(game, player, map);
	init_window(game, map);
	init_image(game);
	// init_game_images();
	init_events(game);
}

void	create_pixel_map(t_game *game, t_map *map)
{
	int	row;
	int	coll;
	int	row_pixel;
	int	coll_pixel;

	game->pixel_map = (char **)malloc(sizeof(char *) * (map->rows * SCALE) + 1);
	if (!game->pixel_map)
		free_map(map, "Failed to allocate memory for pixel map", 1); //add freeing mlx in map too
	row = 0;
	while (row < map->rows)
	{
		row_pixel = 0;
		while (row_pixel < SCALE)
		{
			game->pixel_map[row_pixel + (row * SCALE)] = (char *)malloc(sizeof(char) * (map->cols * SCALE) + 1);
			if (!game->pixel_map[row_pixel + (row * SCALE)])
				free_map(map, "Failed to allocate memory for pixel map", 1); // add freeing the pixel map
			coll = 0;
			while (coll < map->cols)
			{
				coll_pixel = 0;
				while (coll_pixel < SCALE)
				{
					game->pixel_map[row_pixel + (row * SCALE)][(coll * SCALE) + coll_pixel] = map->map[row][coll];
					coll_pixel++;
				}
				coll++;
			}
			row_pixel++;
		}
		row++;
	}
	game->pixel_map[(map->rows * SCALE) + row_pixel] = NULL;
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
	create_pixel_map(game, map);
}

void	init_window(t_game *game, t_map *map)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		free_map(map, "Mlx initialization failed", 1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
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
}

void	init_game_images()
{
	//load images from xpm to img pointers
	//store them in pointers?
}

void	init_events(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &close_window, game);
	mlx_mouse_hook(game->win, mouse_hook, game);
}
