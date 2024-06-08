#include "../../includes/cub3d.h"

void	check_movements(t_game *game)
{
	t_player	*player;
	float		new_x;
	float		new_y;
	int x;
	int	y;

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
	// mlx_mouse_get_pos(game->mlx, game->win, &x, &y);	// need to adjust this, it is changing the player->p_angle as game starts
	mlx_mouse_get_pos(game->win, &x, &y);
	mouse_hook(x, game->player);
	rotate_player(player);
	jumping(game->player);
	move_player(game, new_x, new_y);
}

/* checks whether move is possible and calculates new player->pos.x/y with given move X/Y*/
void	move_player(t_game *game, float new_x, float new_y)
{
	t_player	*player;

	player = game->player;
	if (game->map->map[(int)(new_y) / SCALE][(int)new_x / SCALE] != WALL
		&& game->map->map[(int)(new_y + PSIZE) / SCALE][((int)new_x + PSIZE) / SCALE] != WALL
		&& game->map->map[(int)(new_y + PSIZE) / SCALE][(int)new_x / SCALE] != WALL
		&& game->map->map[(int)(new_y) / SCALE][((int)new_x + PSIZE) / SCALE] != WALL)
		{
			player->pos.y = new_y;
			player->pos.x = new_x;
		}
}

void	rotate_player(t_player *player)
{
	if (player->rot == LEFT)
	{
		player->p_angle -= ROT_SPEED;
		if (player->p_angle < 0)
			player->p_angle += _2PI;
	}
	if (player->rot == RIGHT)
	{
		player->p_angle += ROT_SPEED;
		if (player->p_angle > _2PI)
			player->p_angle -= _2PI;
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
