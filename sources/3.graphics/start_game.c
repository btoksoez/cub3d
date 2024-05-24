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
	move_player(game, new_x, new_y);
}

void	cast_rays(t_game *game)
{
	float		rx;
	float		ry;
	float 		next_vert;
	float 		next_hori;
	float		slope;
	float		intercept;
	float		hit_x_hori;
	float		hit_y_hori;
	float		hit_x_vert;
	float		hit_y_vert;
	// float		len_hori;
	// float		len_vert;
	t_player	*player;

	player = game->player;
	if (player->p_angle < 2 * PI && player->p_angle >= PI)
		next_vert = floorf(player->pos_y / SCALE) * SCALE;
	else
		next_vert = ceilf(player->pos_y / SCALE) * SCALE;
	if (player->p_angle < PI_15 && player->p_angle >= PI_05)
		next_hori = floorf(player->pos_x / SCALE) * SCALE;
	else
		next_hori = ceilf(player->pos_x / SCALE) * SCALE;

	rx = player->pos_x + (100 * cos(player->p_angle));
	ry = player->pos_y + (100 * sin(player->p_angle));
	slope = (ry - player->pos_y) / (rx - player->pos_x);
	intercept = player->pos_y - slope * player->pos_x;

	hit_x_hori = (next_hori - intercept) / (slope - 0);
	hit_y_hori = slope * hit_x_hori + intercept;

	hit_x_vert = (next_vert - intercept) / (slope - 1);
	hit_y_vert = slope * hit_x_vert + intercept;

	draw_point(game, rx, ry, MAGENTA);
	draw_point(game, hit_x_vert, hit_y_vert, BLACK);
	draw_point(game, hit_x_hori, hit_y_hori, BLACK);

	// if (player->p_angle > 0 && player->p_angle <= PI_05)	//looking north east
	// {
	// 	len_hori = fabs(player->pos_y - next_hori) / cos(fabs(PI_05 - player->p_angle));
	// 	len_vert = fabs(player->pos_x - next_vert) / cos(fabs(player->p_angle));
	// }
	// if (player->p_angle > PI_05 && player->p_angle <= PI)	//looking north west
	// {
	// 	len_hori = fabs(player->pos_y - next_hori) / cos(fabs(player->p_angle - PI_05));
	// 	len_vert = fabs(player->pos_x - next_vert) / cos(fabs(PI - player->p_angle));
	// }
	// if (player->p_angle > PI && player->p_angle <= PI_15)	//looking south west
	// {
	// 	len_hori = fabs(player->pos_y - next_hori) / cos(fabs(PI_15 - player->p_angle));
	// 	len_vert = fabs(player->pos_x - next_vert) / cos(fabs(player->p_angle - PI));
	// }
	// if (player->p_angle > PI_15 && player->p_angle <= 2 * PI)	//looking south east
	// {
	// 	len_hori = fabs(player->pos_y - next_hori) / cos(fabs(player->p_angle - PI_15));
	// 	len_vert = fabs(player->pos_x - next_vert) / cos(fabs(2 * PI - player->p_angle));
	// }

	// printf("lens: %f, %f\n", len_hori, len_vert);

	// if (len_hori < len_vert)
	// {
	// 	if (game->map->map[(int)hit_y_hori / SCALE][(int)hit_x_hori / SCALE] == WALL)
	// 		printf("hort\n");
	// 		//draw_line(game, player->pos_x, player->pos_y, hit_x_hori, hit_y_hori, MAGENTA); //after stop, send this to raycaster
	// }
	// if (len_hori >= len_vert)
	// {
	// 	if (game->map->map[(int)hit_y_vert / SCALE][(int)hit_x_vert / SCALE] == WALL)
	// 		printf("vert\n");
	// 		// draw_line(game, player->pos_x, player->pos_y, hit_x_vert, hit_y_vert, MAGENTA); //after stop, send this to raycaster
	// }


	// if (rx % SCALE != 0)

	// ry = player->pos_y + (MOVE * sin(player->p_angle));
	// game->map->map[(int)(new_y) / SCALE][(int)new_x / SCALE] != WALL
	// 	&& game->map->map[(int)(new_y + PSIZE) / SCALE][((int)new_x + PSIZE) / SCALE] != WALL
	// 	&& game->map->map[(int)(new_y + PSIZE) / SCALE][(int)new_x / SCALE] != WALL
	// 	&& game->map->map[(int)(new_y) / SCALE][((int)new_x + PSIZE) / SCALE] != WALL)
}

int	render(t_game *game)
{
	// delete_image?
	hook_player(game);	//sets new pos of player based on u_d, l_r
	render_2dgame(game);
	cast_rays(game);
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

void draw_point(t_game *game, int x, int y, int color)
{
    int size = 10; // Size of the point
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            put_pixel_to_img(game, x + i, y + j, color);
        }
    }
}
