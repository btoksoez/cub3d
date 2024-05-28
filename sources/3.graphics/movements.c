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
		new_x = player->pos.x + (MOVE * cos(player->p_angle));
		new_y = player->pos.y + (MOVE * sin(player->p_angle));
	}
	if (player->up_down == DOWN)
	{
		new_x = player->pos.x + (MOVE * cos(player->p_angle + PI));
		new_y = player->pos.y + (MOVE * sin(player->p_angle + PI));
	}
	if (player->left_right == LEFT)
	{
		new_x = player->pos.x + (MOVE * cos(player->p_angle - PI_05));
		new_y = player->pos.y + (MOVE * sin(player->p_angle - PI_05));
	}
	if (player->left_right == RIGHT)
	{
		new_x = player->pos.x + (MOVE * cos(player->p_angle + PI_05));
		new_y = player->pos.y + (MOVE * sin(player->p_angle + PI_05));
	}
	move_player(game, new_x, new_y);
}
