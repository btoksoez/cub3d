/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enemies_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:57:33 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 18:57:47 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	get_enemy_positions_aux(t_enemy **enemy, t_point dir, int i)
{
	if (enemy[i]->type == OFFICER)
	{
		enemy[i]->size = 5;
		enemy[i]->speed = 20;
	}
	else if (enemy[i]->type == BOSS)
	{
		enemy[i]->size = 30;
		enemy[i]->speed = 1;
	}
	else
	{
		enemy[i]->size = 15;
		enemy[i]->speed = 3;
	}
	enemy[i]->left.x = enemy[i]->pos.x - dir.y * enemy[i]->size / 2;
	enemy[i]->left.y = enemy[i]->pos.y + dir.x * enemy[i]->size / 2;
	enemy[i]->right.x = enemy[i]->pos.x + dir.y * enemy[i]->size / 2;
	enemy[i]->right.y = enemy[i]->pos.y - dir.x * enemy[i]->size / 2;
	enemy[i]->frame = 0;
	enemy[i]->speed = 1;
	enemy[i]->dir_vec = dir;
}

void	get_enemy_positions(t_game *game)
{
	t_enemy	**enemy;
	t_point	dir;
	int		i;

	i = 0;
	enemy = game->enemies;
	while (i < game->enemy_count)
	{
		dir = get_normalized_vector(enemy[i]->pos, game->player->pos);
		get_enemy_positions_aux(enemy, dir, i);
	}
}
