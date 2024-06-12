/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:48:44 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 15:48:45 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
