/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:49:31 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 15:49:32 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	init_map(t_map *map)
{
	if (map == NULL)
		return ;
	map->map = NULL;
	map->rows = 0;
	map->player.x = 0;
	map->player.y = 0;
	map->player_dir = 0;
	map->cols = 0;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->f_color.red = -1;
	map->f_color.green = -1;
	map->f_color.blue = -1;
	map->c_color.red = -1;
	map->c_color.green = -1;
	map->c_color.blue = -1;
	map->enemy_count = 0;
	map->enemies = malloc(sizeof(t_enemy *));
	if (!map->enemies)
		error_message(map, "Malloc error enemies");
}
