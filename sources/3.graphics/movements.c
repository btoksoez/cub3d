#include "../../includes/cub3d.h"

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
		new_x = player->pos.x + (player->speed * (float)cos(player->p_angle));
		new_y = player->pos.y + (player->speed * (float)sin(player->p_angle));
	}
	if (player->up_down == DOWN)
	{
		new_x = player->pos.x + (player->speed * (float)cos(player->p_angle + PI));
		new_y = player->pos.y + (player->speed * (float)sin(player->p_angle + PI));
	}
	if (player->left_right == LEFT)
	{
		new_x = player->pos.x + (player->speed * (float)cos(player->p_angle - _05PI));
		new_y = player->pos.y + (player->speed * (float)sin(player->p_angle - _05PI));
	}
	if (player->left_right == RIGHT)
	{
		new_x = player->pos.x + (player->speed * (float)cos(player->p_angle + _05PI));
		new_y = player->pos.y + (player->speed * (float)sin(player->p_angle + _05PI));
	}
	rotate_player(player);
	move_player(game, new_x, new_y);
}

void	move_player(t_game *game, float new_x, float new_y)
{
 	t_player	*player;
	int			wall_in_x;
	int			wall_in_y;

	player = game->player;
	wall_in_x = game->map->map[(int)(player->pos.y / SCALE)][(int)(new_x / SCALE)] == WALL
				|| game->map->map[(int)(player->pos.y + PSIZE) / SCALE][((int)(new_x + PSIZE)) / SCALE] == WALL
				|| game->map->map[(int)(player->pos.y + PSIZE) / SCALE][(int)new_x / SCALE] == WALL
				|| game->map->map[(int)(player->pos.y) / SCALE][((int)new_x + PSIZE) / SCALE] == WALL;

	wall_in_y = game->map->map[(int)(new_y / SCALE)][(int)(player->pos.x / SCALE)] == WALL
				|| game->map->map[(int)(new_y + PSIZE) / SCALE][(int)(player->pos.x + PSIZE) / SCALE] == WALL
				|| game->map->map[(int)(new_y + PSIZE) / SCALE][(int)player->pos.x / SCALE] == WALL
				|| game->map->map[(int)(new_y) / SCALE][((int)player->pos.x + PSIZE) / SCALE] == WALL;

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
		player->p_angle -= (float)ROT_SPEED;
		if (player->p_angle < 0)
			player->p_angle += _2PI;
	}
	if (player->rot == RIGHT)
	{
		player->p_angle += (float)ROT_SPEED;
		if (player->p_angle > _2PI)
			player->p_angle -= _2PI;
	}
}

