/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:20:53 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 20:40:10 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	draw_line(t_game *game, t_point_i start, t_point_i end)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(end.x - start.x);
	dy = abs(end.y - start.y);
	if (start.x < end.x)
		sx = 1;
	else
		sx = -1;
	if (start.y < end.y)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (true)
	{
		put_pixel_to_img(game, start.x, start.y, BLUE);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start.y += sy;
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
	t_point		center;

	player = game->player;
	mini.player.x = ((WIDTH - (WIDTH / 5) + (WIDTH / SCALE)) + (player->pos.x
				/ 2));
	mini.player.y = ((HEIGHT - (HEIGHT / 5) + (HEIGHT / SCALE)) + (player->pos.y
				/ 2));
	center.x = ((WIDTH - (WIDTH / 5) + (WIDTH / SCALE)) + ((MINI_SCALE * 7) / 2)
			- MINI_PCENTER);
	center.y = ((HEIGHT - (HEIGHT / 5) + (HEIGHT / SCALE)) + ((MINI_SCALE * 5)
				/ 2) - MINI_PCENTER);
	if ((player->pos.x <= mini.hori_vision)
		&& (player->pos.y <= mini.vert_vision))
		render_player(game, mini.player.x, mini.player.y);
	else if (player->pos.y <= mini.vert_vision)
		render_player(game, center.x, mini.player.y);
	else if (player->pos.x <= mini.hori_vision)
		render_player(game, mini.player.x, center.y);
	else
		render_player(game, center.x, center.y);
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
