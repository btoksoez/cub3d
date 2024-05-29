#include "../../includes/cub3d.h"

void	init_minimap(t_game *game, t_minimap *mm)
{
	mm->start.x = WIDTH - MM_WIDTH;
	mm->start.y = HEIGHT - MM_HEIGHT;
	mm->pos_player.x = (int)game->player->pos.x;
	mm->pos_player.y = (int)game->player->pos.y;
	mm->start_map.x = 0;
	mm->start_map.y = 0;
	mm->end_map.x = game->map->cols;
	mm->end_map.x = game->map->rows;
	// mm->start_map.x = max(0, mm->pos_player.x - MM_WIDTH / 2);
	// mm->start_map.y = max(0, mm->pos_player.y - MM_HEIGHT/ 2);
	// mm->end_map.x = min(game->map->cols, mm->pos_player.x + MM_WIDTH / 2);
	// mm->end_map.x = min(game->map->rows, mm->pos_player.y + MM_HEIGHT / 2);
}

void	minimap(t_game *game)
{
	t_minimap	mm;
	int			x;
	int			y;

	init_minimap(game, &mm);
	render_minimap(game, mm.start.x, mm.start.y, MM_SCREEN);
	y = mm.start_map.y;
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->cols)
		{
			if (game->map->map[y][x] == WALL)
				render_minimap(game, mm.start.x + x * MM_SCALE, mm.start.y + y * MM_SCALE, WALLS);
			if (game->map->map[y][x] == EMPTY)
				render_minimap(game, mm.start.x + x  * MM_SCALE, mm.start.y + y * MM_SCALE, SPACE);
			x++;
		}
		y++;
	}
	render_minimap(game, mm.start.x + mm.pos_player.x * MM_SCALE, mm.start.y + mm.pos_player.y * MM_SCALE, PLAYER_);
}

void	render_minimap(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;
	int	line_length;
	int	end_x;
	int	end_y;

	if (color == MM_SCREEN)
	{
		width = MM_WIDTH;
		height = MM_HEIGHT;
	}
	else if (color == PLAYER_)
	{
		line_length = MM_SCALE;
		end_x = (start_x + PCENTER) + (line_length * cos(game->player->p_angle));
		end_y = (start_y + PCENTER) + (line_length * sin(game->player->p_angle));
		draw_line(game, (start_x + PCENTER), (start_y + PCENTER), end_x, end_y, color);
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
