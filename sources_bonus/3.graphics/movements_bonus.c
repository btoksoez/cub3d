/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:48:49 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 15:48:50 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	check_movements(t_game *game)
{
	t_player	*player;
	float		new_x;
	float		new_y;

	player = game->player;
	new_x = player->pos.x;
	new_y = player->pos.y;
	if (player->up_down == UP)
	{
		new_x = player->pos.x + (player->speed * cos(player->p_angle));
		new_y = player->pos.y + (player->speed * sin(player->p_angle));
	}
	if (player->up_down == DOWN)
	{
		new_x = player->pos.x + (player->speed * cos(player->p_angle + PI));
		new_y = player->pos.y + (player->speed * sin(player->p_angle + PI));
	}
	if (player->left_right == LEFT)
	{
		new_x = player->pos.x + (player->speed * cos(player->p_angle - _05PI));
		new_y = player->pos.y + (player->speed * sin(player->p_angle - _05PI));
	}
	if (player->left_right == RIGHT)
	{
		new_x = player->pos.x + (player->speed * cos(player->p_angle + _05PI));
		new_y = player->pos.y + (player->speed * sin(player->p_angle + _05PI));
	}
	rotate_player(player);
	jumping(game->player);
	move_player(game, new_x, new_y);
}

/* checks whether move is possible and calculates new player->pos.x/y with given move X/Y*/
void	move_player(t_game *game, float new_x, float new_y)
{
	t_player	*player;
	int			wall_in_x;
	int			wall_in_y;

	player = game->player;
	wall_in_x = game->map->map[(int)(player->pos.y / SCALE)][(int)(new_x
			/ SCALE)] == WALL || game->map->map[(int)(player->pos.y + PSIZE)
		/ SCALE][((int)(new_x + PSIZE)) / SCALE] == WALL
		|| game->map->map[(int)(player->pos.y + PSIZE) / SCALE][(int)new_x
		/ SCALE] == WALL || game->map->map[(int)(player->pos.y)
		/ SCALE][((int)new_x + PSIZE) / SCALE] == WALL;
	wall_in_y = game->map->map[(int)(new_y / SCALE)][(int)(player->pos.x
			/ SCALE)] == WALL || game->map->map[(int)(new_y + PSIZE)
		/ SCALE][(int)(player->pos.x + PSIZE) / SCALE] == WALL
		|| game->map->map[(int)(new_y + PSIZE) / SCALE][(int)player->pos.x
		/ SCALE] == WALL || game->map->map[(int)(new_y)
		/ SCALE][((int)player->pos.x + PSIZE) / SCALE] == WALL;
	if (!wall_in_x && !wall_in_y)
	{
		player->pos.y = new_y;
		player->pos.x = new_x;
	}
	else if (!wall_in_x)
		player->pos.x = new_x;
	else if (!wall_in_y)
		player->pos.y = new_y;
}

void	rotate_player(t_player *player)
{
	if (player->rot == LEFT)
	{
		player->p_angle -= ROT_SPEED;
		if (player->p_angle < 0)
			player->p_angle += 2 * PI;
	}
	if (player->rot == RIGHT)
	{
		player->p_angle += ROT_SPEED;
		if (player->p_angle > 2 * PI)
			player->p_angle -= 2 * PI;
	}
}

void	jumping(t_player *player)
{
	float	jump_progress;
	float	jump_speed;
	float	fall_progress;
	float	fall_speed;

	if (player->jumping && !player->jump_peak)
	{
		jump_progress = player->jump_height / (float)MAX_JUMP_HEIGHT;
		jump_speed = MAX_JUMP_SPEED * (1.0 - jump_progress);
		player->jump_height += jump_speed;
		if (player->jump_height >= MAX_JUMP_HEIGHT || jump_speed < 0.5)
			player->jump_peak = true;
	}
	else if (player->jump_peak || !player->jumping)
	{
		fall_progress = 1.0 - (player->jump_height / (float)MAX_JUMP_HEIGHT);
		fall_speed = MAX_JUMP_SPEED * sqrt(fall_progress);
		player->jump_height -= fall_speed;
		if (player->jump_height <= 0)
		{
			player->jump_height = 0;
			player->jumping = false;
			player->jump_peak = false;
		}
	}
}
