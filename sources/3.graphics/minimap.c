#include "../../includes/cub3d.h"

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
	printf("start_map: %f, %f\nendmap: %f %f\n\n", mm->start_map.x, mm->start_map.y, mm->end_map.x, mm->end_map.y);
	printf("playerpos: %f %f\n\n", game->player->pos.x, game->player->pos.y);
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
	// printf("Rendering player at (%f, %f) \n", game->player->pos.x, game->player->pos.y);
	render_minimap(game, mm.pos_player.x, mm.pos_player.y, RED);
}

void	render_minimap(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;
	// int	line_length;
	// int	end_x;
	// int	end_y;

	if (color == MM_SCREEN)
	{
		width = MM_WIDTH;
		height = MM_HEIGHT;
	}
	else if (color == RED)
	{
		// line_length = MM_SCALE;
		// end_x = (start_x + PCENTER) + (line_length * cos(game->player->p_angle));
		// end_y = (start_y + PCENTER) + (line_length * sin(game->player->p_angle));
		// draw_line(game, (start_x + PCENTER), (start_y + PCENTER), end_x, end_y, color);
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
