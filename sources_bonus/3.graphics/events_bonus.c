/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:47:28 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 15:48:14 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

void	init_events(t_game *game)
{
	mlx_hook(game->win, KEYPRESS, KEYPRESSMASK, &key_press, game);
	mlx_hook(game->win, KEYRELEASE, KEYRELEASEMASK, &key_release, game);
	mlx_hook(game->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, &close_window,
		game);
}

// add shooting, space, reload ...
int	key_press(int key, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (key == ESC)
		close_window(game, 0, QUIT);
	if (key == W)
		player->up_down = UP;
	if (key == A)
		player->left_right = LEFT;
	if (key == S)
		player->up_down = DOWN;
	if (key == D)
		player->left_right = RIGHT;
	if (key == LEFT_KEY)
		player->rot = LEFT;
	if (key == RIGHT_KEY)
		player->rot = RIGHT;
	if (key == SHIFT)
		player->speed = 2;
	if (key == SPACEBAR)
	{
		player->jumping = true;
		player->jump_peak = false;
	}
	if (key == SHOOT)
		player->shooting = 10;
	if (key == SWITCH)
		player->weapon = (player->weapon + 1) % 3;
	return (0);
}

int	key_release(int key, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (key == W)
		player->up_down = RESET;
	if (key == A)
		player->left_right = RESET;
	if (key == S)
		player->up_down = RESET;
	if (key == D)
		player->left_right = RESET;
	if (key == LEFT_KEY)
		player->rot = RESET;
	if (key == RIGHT_KEY)
		player->rot = RESET;
	if (key == SHIFT)
		player->speed = 1;
	return (0);
}
