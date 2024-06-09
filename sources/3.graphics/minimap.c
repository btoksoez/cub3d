#include "../../includes/cub3d.h"

// render player + 3 up, 3 left, 3 down, 3 right
// if player only has 1 on left, right, up, down, then render 5 on the other direction, same for 2, rander 4
// will have problems with maps smaller than 7x7

void	render_player_and_rays(t_game *game, t_raycaster *ray, t_minimap mini)
{
	t_player	*player;

	player = game->player;
	if ((player->pos.x <= mini.hori_vision) && (player->pos.y <= mini.vert_vision))
		render_player(game, MINI_PLAYER_X, MINI_PLAYER_Y);
	else if (player->pos.y <= mini.vert_vision)
		render_player(game, CENTER_X, MINI_PLAYER_Y);
	else if (player->pos.x <= mini.hori_vision)
		render_player(game, MINI_PLAYER_X, CENTER_Y);
	else
		render_player(game, CENTER_X, CENTER_Y);
	cast_2d_rays(game, ray, mini);
}

void	get_start_x(t_player *player, t_minimap *mini)
{
	mini->start_x = player->pos.x;
	if (mini->start_x - mini->hori_vision >= 0)
		mini->start_x -= mini->hori_vision;
	else
		mini->start_x = 0;
}

void	init_minimap(t_player *player, t_minimap *mini)
{
	mini->hori_vision = (SCALE * MINI_COLS / 2) - MINI_PSIZE;
	mini->vert_vision = (SCALE * MINI_ROWS / 2) - MINI_PSIZE;
	mini->start_y = player->pos.y;
	get_start_x(player, mini);
	if (mini->start_y - mini->vert_vision >= 0)
		mini->start_y -= mini->vert_vision;
	else
		mini->start_y = 0;
	mini->end_x = mini->start_x + (SCALE * MINI_COLS);
	mini->end_y = mini->start_y + (SCALE * MINI_ROWS);
	mini->initial_x = mini->start_x;
	mini->initial_y = mini->start_y;
}

void	minimap(t_game *game, t_raycaster *ray)
{
	t_player	*player;
	t_minimap	mini;
	int			y;
	int			x;

	player = game->player;
	init_minimap(player, &mini);
	y = mini.start_y;
	while (y < mini.end_y)
	{
		get_start_x(player, &mini);
		x = mini.start_x;
		while (x < mini.end_x)
		{
			if (game->map->map[(int)(y / SCALE)][(int)(x / SCALE)] == WALL)
				put_pixel_to_img(game, CURRENT_X, CURRENT_Y, WALLS);
			else if (game->map->map[(int)(y / SCALE)][(int)(x / SCALE)] == EMPTY)
				put_pixel_to_img(game, CURRENT_X, CURRENT_Y, SPACE);
			else
				put_pixel_to_img(game, CURRENT_X, CURRENT_Y, SCREEN);
			mini.start_x++;
			x += SCALE_FACTOR;
		}
		mini.start_y++;
		y += SCALE_FACTOR;
	}
	render_player_and_rays(game, ray, mini);
}

void	render_player(t_game *game, int start_x, int start_y)
{
	int	width;
	int	height;
	int	x;
	int	y;

	width = PSIZE / 2;
	height = PSIZE / 2;
	y = start_y;
	while (y < start_y + height)
	{
		x = start_x;
		while (x < start_x + width)
		{
			put_pixel_to_img(game, x, y, PLAYER_);
			x++;
		}
		y++;
	}
}

void	draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;

	dx = abs(end_x - start_x);
	dy = abs(end_y - start_y);
	sx = (start_x < end_x) ? 1 : -1;
	sy = (start_y < end_y) ? 1 : -1;
	err = dx - dy;
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
