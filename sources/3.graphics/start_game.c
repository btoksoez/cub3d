#include "../../includes/cub3d.h"

void	start_game(t_map *map)
{
	t_game		game;
	t_player	player;

	init_mlx(&game, &player, map);
	mlx_loop_hook(game.mlx, &render, &game);
	mlx_loop(game.mlx);
}

/* this should calculate the move based on flags and call move and rotoate functions */
void	hook_player(t_game *game)
{
	t_player	*player;
	float		new_x;
	float		new_y;

	player = game->player;
	new_x = player->pos_x;
	new_y = player->pos_y;
	printf("Pos2: %f %f\n", player->pos_x, player->pos_y);
	if (player->rot == LEFT)
		player->p_angle = fmod(player->p_angle - ROT_SPEED, 2.0 * PI);
	if (player->rot == RIGHT)
		player->p_angle = fmod(player->p_angle + ROT_SPEED, 2.0 * PI);
	if (player->up_down == UP)
	{
		new_x = player->pos_x + (MOVE * cos(player->p_angle));
		new_y = player->pos_y + (MOVE * sin(player->p_angle));
	}
	if (player->up_down == DOWN)
	{
		new_x = player->pos_x + (MOVE * cos(player->p_angle + PI));
		new_y = player->pos_y + (MOVE * sin(player->p_angle + PI));
	}
	if (player->left_right == LEFT)
	{
		new_x = player->pos_x + (MOVE * cos(player->p_angle - PI_05));
		new_y = player->pos_y + (MOVE * sin(player->p_angle - PI_05));
	}
	if (player->left_right == RIGHT)
	{
		new_x = player->pos_x + (MOVE * cos(player->p_angle + PI_05));
		new_y = player->pos_y + (MOVE * sin(player->p_angle + PI_05));
	}
	printf("angle: %f", player->p_angle - PI_05);
	printf("Pos3: %f %f\n", player->pos_x, player->pos_y);
	printf("Old: %f, %f\nNew: %f, %f", player->pos_x, player->pos_y, new_x, new_y);
	move_player(game, new_x, new_y);
}

int	render(t_game *game)
{
	// delete_image?
	hook_player(game);	//sets new pos of player based on u_d, l_r
	render_2dgame(game);
	// cast_rays()
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}

// Somehow need to scale map to screensize, so that for any map, the screensize if still 1080 x 720
void	render_2dgame(t_game *game)
{
	int			y;
	int			x;
	t_player	*player;

	player = game->player;
	render_image(game, 0, 0, SCREEN);
	y = 0;
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->max_coll)
		{
			if (game->map->map[y][x] == WALL)
				render_image(game, x * SCALE, y * SCALE, WALLS);
			if (game->map->map[y][x] == EMPTY)
				render_image(game, x * SCALE, y * SCALE, SPACE);
			render_image(game, player->pos_x, player->pos_y, PLAYER_);
			x++;
		}
		y++;
	}
}

void	render_image(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;
	int	line_length;
	int	end_x;
	int	end_y;

	if (color == SCREEN)
	{
		width = game->width;
		height = game->height;
	}
	else if (color == PLAYER_)
	{
		line_length = SCALE;					// Change this to control the length of the line
		end_x = (start_x + PCENTER) + (line_length * cos(game->player->p_angle));
		end_y = (start_y + PCENTER) + (line_length * sin(game->player->p_angle));
		draw_line(game, (start_x + PCENTER), (start_y + PCENTER), end_x, end_y, color);
		width = PSIZE;
		height = PSIZE;
	}
	else
	{
		width = SCALE;
		height = SCALE;
	}
	for (int y = start_y; y < start_y + width; y++)
	{
		for (int x = start_x; x < start_x + height; x++)
		{
			if (x == start_x || x == start_x + width - 1 || y == start_y || y == start_y + height - 1)
				put_pixel_to_img(game, x, y, BLACK);
			else
				put_pixel_to_img(game, x, y, color);
		}
	}
}

void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < game->width && y >= 0 && y < game->height)
	{
		int offset = (y * game->img.line_len) + (x * (game->img.bits_per_pixel / 8));
		*(unsigned int *)(game->img.pixels_ptr + offset) = color;
	}
}

void	draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color)
{
	// Bresenham's line algorithm
	int dx = abs(end_x - start_x);
	int dy = abs(end_y - start_y);
	int sx = (start_x < end_x) ? 1 : -1;
	int sy = (start_y < end_y) ? 1 : -1;
	int err = dx - dy;

	while (true)
	{
		put_pixel_to_img(game, start_x, start_y, color);
		if (start_x == end_x && start_y == end_y)
			break ;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start_x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start_y += sy;
		}
	}
}
