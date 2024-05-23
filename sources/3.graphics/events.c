#include "../../includes/cub3d.h"

// add shooting, space, reload ...
int	key_press(int key, t_game *game)
{
	int	x;
	int	y;

	x = game->player_x;
	y = game->player_y;
	if (key == ESC)
		close_window(game, 0, ESC);
	if (key == W)
		if (game->map->map[(y - BUFFER) / SCALE][x / SCALE] != WALL)
			game->player_y -= MOVE;				// we need to move the player a minimum amount
	if (key == A)								// if it isn't touching the wall yet
		if (game->map->map[y / SCALE][(x - BUFFER) / SCALE] != WALL)
			game->player_x -= MOVE;
	if (key == S)
		if (game->map->map[(y + PSIZE) / SCALE][x / SCALE] != WALL)
			game->player_y += MOVE;
	if (key == D)
		if (game->map->map[y / SCALE][(x + PSIZE) / SCALE] != WALL)
			game->player_x += MOVE;
	if (key == LEFT)
		game->player_angle = fmod(game->player_angle - 0.1, 2.0 * PI);
	if (key == RIGHT)
		game->player_angle = fmod(game->player_angle + 0.1, 2.0 * PI);
	render_2dgame(game);
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
