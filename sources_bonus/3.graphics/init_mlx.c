#include "../../includes_bonus/cub3d.h"

void	init_mlx(t_game *game, t_textures *textures, t_player *player, t_map *map)
{
	init_game_struct(game, player, map);
	init_window(game, map);
	init_image(game);
	init_textures(game, textures);
	init_events(game);
}

void	get_enemy_positions(t_game *game)
{
	t_enemy	**enemy;
	t_point	dir;
	int		i;

	i = 0;
	enemy = game->enemies;
	while (i < game->enemy_count)
	{
		dir = get_normalized_vector(enemy[i]->pos, game->player->pos);
		enemy[i]->left.x = enemy[i]->pos.x - dir.y * PCENTER;
		enemy[i]->left.y = enemy[i]->pos.y + dir.x * PCENTER;
		enemy[i]->right.x = enemy[i]->pos.x + dir.y * PCENTER;
		enemy[i]->right.y = enemy[i]->pos.y - dir.x * PCENTER;
		enemy[i]->frame = 0;
		i++;
	}
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
	player->shooting = 0;
	player->weapon = GUN;
	game->enemies = map->enemies;
	game->enemy_count = map->enemy_count;
	get_enemy_positions(game);
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

int	convert(t_rgb color)
{
	return (color.red << 16 | color.green << 8 | color.blue);
}
