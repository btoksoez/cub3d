#include "../../includes/cub3d.h"

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		close_window(game, 0, ESC);
	if (key == W)
	{
		if (game->map->map[(int)(game->player_y - 0.6)/ SCALE][(int)game->player_x / SCALE] != WALL)
			game->player_y -= 0.5;
	}
	if (key == A)
	{
		if (game->map->map[(int)(game->player_y)/ SCALE][(int)(game->player_x - 0.6) / SCALE] != WALL)
			game->player_x -= 0.5;
	}
	if (key == S)
	{
		if (game->map->map[(int)(game->player_y + 0.6 + PSIZE)/ SCALE][(int)game->player_x / SCALE] != WALL)
			game->player_y += 0.5;
	}
	if (key == D)
	{
		if (game->map->map[(int)(game->player_y)/ SCALE][(int)(game->player_x + 0.6 + PSIZE) / SCALE] != WALL)
			game->player_x += 0.5;
	}
	if (key == LEFT)
	{
		game->player_angle = fmod(game->player_angle - 0.1, 2.0 * PI);
	}
	if (key == RIGHT)
		game->player_angle = fmod(game->player_angle + 0.1, 2.0 * PI);
	printf("player x: %f, PLayer Y: %f\n", game->player_x, game->player_y);
	// add shooting, space, reload ...
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
