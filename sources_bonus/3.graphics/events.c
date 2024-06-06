#include "../../includes_bonus/cub3d.h"

void	init_events(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->mapwin, KeyPress, KeyPressMask, &key_press, game);

	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->mapwin, KeyRelease, KeyReleaseMask, &key_release, game);

	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &close_window, game);
	mlx_hook(game->mapwin, DestroyNotify, StructureNotifyMask, &close_window, game);

	mlx_mouse_hook(game->win, mouse_hook, game);
	mlx_mouse_hook(game->mapwin, mouse_hook, game);
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
		player->speed = 6;
	if (key == SPACEBAR)
	{
		player->jumping= true;
		player->jump_peak = false;
	}
	if (key == SHOOT)
		player->shooting = 10;
	if (key == SWITCH)
		player->weapon = (player->weapon + 1) % 4;
	return (0);
}

int key_release(int key, t_game *game)
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
		player->speed = 2;
	return (0);

}

int	mouse_hook(int button, int x, int y, t_game *game)
{
	if (button == LEFT_BTN)
	{

		(void)x;
	}
	if (button == RIGHT_BTN)
	{

		(void)y;
	}
	(void)game;
	return (0);
}
