#include "../../includes/cub3d.h"

// render player + 3 up, 3 left, 3 down, 3 right
// if player only has 1 on left, right, up, down, then render 5 on the other direction, same for 2, rander 4
// will have problems with maps smaller than 7x7

void	minimap(t_game *game)
{
	t_player	*player;
	int x;
	int y;
	int	end_x;
	int	end_y;
	int	coll;
	int	row;

	player = game->player;
	x = player->pos.x / SCALE;
	y = player->pos.y / SCALE;
	if (x - 3 >= 0)
		x -= 3;
	else
		x = 0;
	if (y - 2 >= 0)
		y -= 2;
	else
		y = 0;
	end_x = x + 7;
	end_y = y + 5;
	row = 0;
	while (y < end_y)
	{
		coll = 0;
		x = player->pos.x / SCALE;
		if (x - 3 >= 0)
			x -= 3;
		else
			x = 0;
		while (x < end_x)
		{
			if (game->map->map[y][x] == WALL)
				render_minimap(game, coll * SCALE / 2, row * SCALE / 2, WALLS);
			if (game->map->map[y][x] == EMPTY)
				render_minimap(game, coll * SCALE / 2, row * SCALE / 2, SPACE);
			if (coll == 3 && row == 2)
				render_minimap(game, coll * SCALE / 2, row * SCALE / 2, PLAYER_);
			x++;
			coll++;
		}
		row++;
		y++;
	}
}

void	render_minimap(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;

	if (color == PLAYER_)
	{
		width = PSIZE / 2;
		height = PSIZE / 2;
	}
	else
	{
		width = SCALE / 2;
		height = SCALE / 2;
	}
	int	x;
	int	y = start_y;

	while (y < start_y + height)
	{
		x = start_x;
		while (x < start_x + width)
		{
			if (x == start_x || x == start_x + width - 1 || y == start_y || y == start_y + height - 1)
				put_pixel_to_img(game, x + (WIDTH - WIDTH / 5), y + (HEIGHT - HEIGHT / 5), BLACK);
			else
				put_pixel_to_img(game, x + (WIDTH - WIDTH / 5), y + (HEIGHT - HEIGHT / 5), color);
			x++;
		}
		y++;
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
