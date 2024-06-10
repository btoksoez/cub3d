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
		if (enemy[i]->type == OFFICER)
		{
			printf("officer\n");
			enemy[i]->size = 5;
			enemy[i]->speed = 2;
		}
		else if (enemy[i]->type == BOSS)
		{
			printf("boss\n");
			enemy[i]->size = 30;
			enemy[i]->speed = 1;
		}
		else
		{
			enemy[i]->size = 15;
			enemy[i]->speed = 3;
		}
		enemy[i]->left.x = enemy[i]->pos.x - dir.y * enemy[i]->size / 2;
		enemy[i]->left.y = enemy[i]->pos.y + dir.x * enemy[i]->size / 2;
		enemy[i]->right.x = enemy[i]->pos.x + dir.y * enemy[i]->size / 2;
		enemy[i]->right.y = enemy[i]->pos.y - dir.x * enemy[i]->size / 2;
		enemy[i]->frame = 0;
		enemy[i]->speed = 1;
		enemy[i]->dir_vec = dir;
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
	game->is_player_dead = false;
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

int	convert(t_rgb color)
{
	return (color.red << 16 | color.green << 8 | color.blue);
}
