/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:02:23 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 21:10:04 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	draw_ray_aux1(t_point_i *start, t_point_i *end, t_point close_to_b)
{
	start->x = close_to_b.x;
	start->y = close_to_b.y;
	end->x = close_to_b.x;
	end->y = close_to_b.y;
}

void	draw_ray_aux2(t_point_i *start, t_point_i *end, t_point close_to_b, t_point centered)
{
	start->x = centered.x;
	start->y = close_to_b.y;
	end->x = centered.x;
	end->y = close_to_b.y;
}

void	draw_ray_aux3(t_point_i *start, t_point_i *end, t_point close_to_b, t_point centered)
{
	start->x = close_to_b.x;
	start->y = centered.y;
	end->x = close_to_b.x;
	end->y = centered.y;
}

void	draw_ray_aux4(t_point_i *start, t_point_i *end, t_point centered)
{
	start->x = centered.x;
	start->y = centered.y;
	end->x = centered.x;
	end->y = centered.y;
}
