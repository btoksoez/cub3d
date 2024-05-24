#include "../../includes/cub3d.h"

/* checks whether move is possible and calculates new player->pos_x/y with given move X/Y*/
void	move_player(t_game *game, float move_x, float move_y)
{
	if (key == W)
		if (game->map->map[(y - BUFFER) / SCALE][x / SCALE] != WALL)
			player->pos_y -= MOVE;				// we need to move the player a minimum amount
	if (key == A)								// if it isn't touching the wall yet
		if (game->map->map[y / SCALE][(x - BUFFER) / SCALE] != WALL)
			player->pos_x -= MOVE;
	if (key == S)
		if (game->map->map[(y + PSIZE) / SCALE][x / SCALE] != WALL)
			player->pos_y += MOVE;
	if (key == D)
		if (game->map->map[y / SCALE][(x + PSIZE) / SCALE] != WALL)
			player->pos_x += MOVE;
	if (key == LEFT)
		player->p_angle = fmod(player->p_angle - 0.1, 2.0 * PI);
	if (key == RIGHT)
		player->p_angle = fmod(player->p_angle + 0.1, 2.0 * PI);
}

// add shooting, space, reload ...
// fix corners of walls
// this should set u_l and l_r and rot flags based on pressed keys
int	key_press(int key, t_game *game)
{
	int			x;
	int			y;
	t_player	*player;

	player = game->player;
	x = player->pos_x;
	y = player->pos_y;
	if (key == ESC)
		close_window(game, 0, ESC);
	if (key == W)
		if (game->map->map[(y - BUFFER) / SCALE][x / SCALE] != WALL)
			player->pos_y -= MOVE;				// we need to move the player a minimum amount
	if (key == A)								// if it isn't touching the wall yet
		if (game->map->map[y / SCALE][(x - BUFFER) / SCALE] != WALL)
			player->pos_x -= MOVE;
	if (key == S)
		if (game->map->map[(y + PSIZE) / SCALE][x / SCALE] != WALL)
			player->pos_y += MOVE;
	if (key == D)
		if (game->map->map[y / SCALE][(x + PSIZE) / SCALE] != WALL)
			player->pos_x += MOVE;
	if (key == LEFT)
		player->p_angle = fmod(player->p_angle - 0.1, 2.0 * PI);
	if (key == RIGHT)
		player->p_angle = fmod(player->p_angle + 0.1, 2.0 * PI);
	render_2dgame(game);
	return (0);
}

// this should set u_l and l_r and rot flags
int key_release(int keysym, t_game *game)
{
	//set vars to 0
	(void)keysym;
	(void)game;
	return (0);

}

int	mouse_hook(int button, int x, int y, t_game *game)
{
	if (button == 4)
	{
		//scroll up
		(void)x;
	}
	if (button == 5)
	{
		//scroll down
		(void)y;
	}
	(void)game;
	return (0);
}
