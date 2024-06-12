#include "../../includes_bonus/cub3d_bonus.h"

void	draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y,
		int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

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
		e2 = 2 * err;
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

void	get_start_x(t_player *player, t_minimap *mini)
{
	mini->start_x = player->pos.x;
	if (mini->start_x - mini->hori_vision >= 0)
		mini->start_x -= mini->hori_vision;
	else
		mini->start_x = 0;
}

void	render_player_and_rays(t_game *game, t_raycaster *ray, t_minimap mini)
{
	t_player	*player;

	player = game->player;
	if ((player->pos.x <= mini.hori_vision)
		&& (player->pos.y <= mini.vert_vision))
		render_player(game, ((WIDTH - (WIDTH / 5) + (WIDTH / SCALE))
				+ (player->pos.x / 2)), ((HEIGHT - (HEIGHT / 5) + (HEIGHT
						/ SCALE)) + (player->pos.y / 2)));
	else if (player->pos.y <= mini.vert_vision)
		render_player(game, ((WIDTH - (WIDTH / 5) + (WIDTH / SCALE))
				+ ((MINI_SCALE * 7) / 2) - MINI_PCENTER), ((HEIGHT - (HEIGHT
						/ 5) + (HEIGHT / SCALE)) + (player->pos.y / 2)));
	else if (player->pos.x <= mini.hori_vision)
		render_player(game, ((WIDTH - (WIDTH / 5) + (WIDTH / SCALE))
				+ (player->pos.x / 2)), ((HEIGHT - (HEIGHT / 5) + (HEIGHT
						/ SCALE)) + ((MINI_SCALE * 5) / 2) - MINI_PCENTER));
	else
		render_player(game, ((WIDTH - (WIDTH / 5) + (WIDTH / SCALE))
				+ ((MINI_SCALE * 7) / 2) - MINI_PCENTER), ((HEIGHT - (HEIGHT
						/ 5) + (HEIGHT / SCALE)) + ((MINI_SCALE * 5) / 2)
				- MINI_PCENTER));
	raycast_2d(game, ray, mini);
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
