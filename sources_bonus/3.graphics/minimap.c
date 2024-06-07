#include "../../includes_bonus/cub3d.h"

void	render_2dgame(t_game *game)
{
	int			y;
	int			x;
	t_player	*player;
	t_enemy		**enemy;
	int			i;

	player = game->player;
	enemy = game->enemies;
	y = 0;
	render_image(game, 0, 0, SCREEN);
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->cols)
		{
			if (game->map->map[y][x] == WALL)
				render_image(game, x * SCALE, y * SCALE, WALLS);
			if (game->map->map[y][x] == EMPTY)
				render_image(game, x * SCALE, y * SCALE, SPACE);
			render_image(game, player->pos.x, player->pos.y, PLAYER_);
			i = 0;
			while (i < game->enemy_count)
			{
				draw_line(game, enemy[i]->left.x, enemy[i]->left.y, enemy[i]->right.x, enemy[i]->right.y, enemy[i]->type);
				i++;
			}
			x++;
		}
		y++;
	}
}

void	render_image(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;

	if (color == SCREEN)
	{
		width = game->width;
		height = game->height;
	}
	else if (color == PLAYER_)
	{
		width = PSIZE;
		height = PSIZE;
	}
	else
	{
		width = SCALE;
		height = SCALE;
	}
	for (int y = start_y; y < start_y + height; y++)
	{
		for (int x = start_x; x < start_x + width; x++)
		{
			if (x == start_x || x == start_x + width - 1 || y == start_y || y == start_y + height - 1)
				put_pixel_to_mapimg(game, x, y, BLACK);
			else
				put_pixel_to_mapimg(game, x, y, color);
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
		put_pixel_to_mapimg(game, start_x, start_y, color);
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

void	put_pixel_to_mapimg(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < game->width && y >= 0 && y < game->height)
	{
		int offset = (y * game->mapimg.line_len) + (x * (game->mapimg.bits_per_pixel / 8));
		*(unsigned int *)(game->mapimg.pixels_ptr + offset) = color;
	}
}

void	init_minimap(t_game *game, t_minimap *mm)
{
	mm->start.x = WIDTH - WIDTH / 5;
	mm->start.y = HEIGHT - HEIGHT / 5;
	mm->pos_player.x = mm->start.x + game->player->pos.x / WIDTH * (WIDTH - mm->start.x);
	mm->pos_player.y = mm->start.y + game->player->pos.y / HEIGHT * (HEIGHT - mm->start.y);
	mm->start_map.x = max(0, mm->pos_player.x - (MM_WIDTH / 2) * 5);
	mm->start_map.y = max(0, mm->pos_player.y - (MM_HEIGHT / 2) * 5);
	mm->end_map.x = min(game->map->cols, mm->pos_player.x + (MM_WIDTH / 2) * 5);
	mm->end_map.y = min(game->map->rows, mm->pos_player.y + (MM_HEIGHT / 2) * 5);
}

void	minimap(t_game *game)
{
	t_minimap	mm;
	int			x;
	int			y;

	init_minimap(game, &mm);
	render_minimap(game, mm.start.x, mm.start.y, MM_SCREEN);
	y = mm.start_map.y / SCALE;
	while (y < mm.end_map.y / SCALE)
	{
		x = mm.start_map.y / SCALE;
		while (x < mm.end_map.x / SCALE)
		{
			if (game->map->map[y][x] == WALL)
				render_minimap(game, mm.start.x + x / 5, mm.start.y + y / 5, WALLS);
			if (game->map->map[y][x] == EMPTY)
				render_minimap(game, mm.start.x + x / 5, mm.start.y + y / 5, SPACE);
			x++;
		}
		y++;
	}
	render_minimap(game, mm.pos_player.x, mm.pos_player.y, RED);
}

void	render_minimap(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;

	if (color == MM_SCREEN)
	{
		width = MM_WIDTH;
		height = MM_HEIGHT;
	}
	else if (color == RED)
	{
		width = PSIZE;
		height = PSIZE;
	}
	else
	{
		width = MM_SCALE;
		height = MM_SCALE;
	}
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
