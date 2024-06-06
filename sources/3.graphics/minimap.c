#include "../../includes/cub3d.h"

// render player + 3 up, 3 left, 3 down, 3 right
// if player only has 1 on left, right, up, down, then render 5 on the other direction, same for 2, rander 4
// will have problems with maps smaller than 7x7

void	minimap(t_game *game)
{
	t_player	*player;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	hori_vision;
	int	vert_vision;
	int	iterate_x;
	int	iterate_y;

	player = game->player;
	start_x = player->pos.x;
	start_y = player->pos.y;
	hori_vision = (SCALE * 3) + (SCALE / 2) - (PSIZE / 2) - 1;
	vert_vision = (SCALE * 2) + (SCALE / 2) - (PSIZE / 2) - 1;
	if (start_x - hori_vision >= 0)
		start_x -= hori_vision;
	else
		start_x = 0;

	if (start_y - vert_vision >= 0)
		start_y -= vert_vision;
	else
		start_y = 0;

	end_x = start_x + (SCALE * 7);
	end_y = start_y + (SCALE * 5);
	iterate_y = start_y;
	int	initial_x = start_x;
	int	initial_y = start_y;
	// int	initial_player_x = player->pos.x;
	// int	initial_player_y = player->pos.y;
	while (iterate_y < end_y)
	{
		start_x = player->pos.x;
		if (start_x - hori_vision >= 0)
			start_x -= hori_vision;
		else
			start_x = 0;
		iterate_x = start_x;
		while (iterate_x < end_x)
		{
			if (game->map->map[(int)(iterate_y / SCALE)][(int)(iterate_x / SCALE)] == WALL)
				put_pixel_to_img(game, start_x - initial_x + MINI_X, start_y - initial_y + MINI_Y, WALLS);
			else if (game->map->map[(int)(iterate_y / SCALE)][(int)(iterate_x / SCALE)] == EMPTY)
				put_pixel_to_img(game, start_x - initial_x  + MINI_X, start_y - initial_y + MINI_Y, SPACE);
			else
				put_pixel_to_img(game, start_x - initial_x  + MINI_X, start_y - initial_y + MINI_Y, GREY);
			render_minimap(game, (player->pos.x / 2) + MINI_X, (player->pos.y / 2)+ MINI_Y, PLAYER_);
			start_x++;
			iterate_x += SCALE / (SCALE / 2);
		}
		start_y++;
		iterate_y += SCALE / (SCALE / 2);
	}
}

void	render_minimap(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;

	width = PSIZE / 2;
	height = PSIZE / 2;
	for (int y = start_y; y < start_y + height; y++)
	{
		for (int x = start_x; x < start_x + width; x++)
		{
			if (x == start_x || x == start_x + width - 1 || y == start_y || y == start_y + height - 1)
				put_pixel_to_img(game, x, y, BLACK);
			else
				put_pixel_to_img(game, x, y, color);
		}
	}
}

void	draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color)
{
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
