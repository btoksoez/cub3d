#include "../../includes/cub3d.h"

void	init_minimap(t_game *game, t_minimap *mm)
{
	mm->start.x = WIDTH - (WIDTH / 5);
	mm->start.y = HEIGHT - (HEIGHT / 5);
	mm->pos_player.x = mm->start.x + (game->player->pos.x / WIDTH) * (WIDTH - mm->start.x) - 5;
	mm->pos_player.y = mm->start.y + (game->player->pos.y / HEIGHT) * (HEIGHT - mm->start.y) - 5;
	// printf("start_map: %f, %f\nendmap: %f %f\n\n", mm->start_map.x, mm->start_map.y, mm->end_map.x, mm->end_map.y);
	// printf("playerpos: %f %f\n\n", game->player->pos.x, game->player->pos.y);
}

void	minimap(t_game *game)
{
	t_minimap	mm;
	int			x;
	int			y;

	init_minimap(game, &mm);
	y = 0;
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->cols)
		{
			if (game->map->map[y][x] == WALL)
				render_minimap(game, mm.start.x + (x * game->xscale) / 5, mm.start.y + (y * game->yscale) / 5, WALLS);
			else if (game->map->map[y][x] == EMPTY)
				render_minimap(game, mm.start.x + (x * game->xscale) / 5, mm.start.y + (y * game->yscale) / 5, SPACE);
			else
				render_minimap(game, mm.start.x + (x * game->xscale) / 5, mm.start.y + (y * game->yscale) / 5, SCREEN);
			render_minimap(game, mm.pos_player.x, mm.pos_player.y, PLAYER_);
			x++;
		}
		y++;
	}
}

void	render_minimap(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;

	if (color == PLAYER_)
	{
		width = game->xscale / 4;
		height = game->yscale / 4;
	}
	else
	{
		width = game->xscale;
		height = game->yscale;
	}
	for (int y = start_y; y < start_y + height; y++)
	{
		for (int x = start_x; x < start_x + width; x++)
		{
			if (x == start_x || x == start_x + width - 1 || y == start_y || y == start_y + height - 1)
				put_pixel_to_img(game, x, y, SCREEN);
			else
				put_pixel_to_img(game, x, y, color);
		}
	}
}
