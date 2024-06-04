#include "../../includes/cub3d.h"

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

/* this should calculate the move based on flags and call move and rotoate functions */
void	hook_player(t_game *game)
{
	t_player	*player;
	float		new_x;
	float		new_y;

	player = game->player;
	new_x = player->pos.x;
	new_y = player->pos.y;
	rotate_player(player);
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
		new_x = player->pos.x + (player->speed * cos(player->p_angle - PI_05));
		new_y = player->pos.y + (player->speed * sin(player->p_angle - PI_05));
	}
	if (player->left_right == RIGHT)
	{
		new_x = player->pos.x + (player->speed * cos(player->p_angle + PI_05));
		new_y = player->pos.y + (player->speed * sin(player->p_angle + PI_05));
	}
	move_player(game, new_x, new_y);
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

