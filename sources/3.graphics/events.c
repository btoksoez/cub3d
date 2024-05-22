#include "../../includes/cub3d.h"

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		close_window(game, 0, ESC);
	else if (key == W || key == UP)
	{
		//
	}
	else if (key == A || key == LEFT)
	{
		//
	}
	else if (key == S || key == DOWN)
	{
		//
	}
	else if (key == D || key == RIGHT)
	{
		//
	}
	// add shooting, space, reload ...
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
