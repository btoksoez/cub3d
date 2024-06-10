#include "../../includes_bonus/cub3d.h"

void	init_events(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, &key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &key_release, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &close_window, game);
	mlx_mouse_hook(game->win, mouse_hook, game);
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

// need to fix if mouse gets to screen edge
int	mouse_hook(int x, t_player *player)
{
	int	delta_x;

	delta_x = x - player->prev_mouse_x;
	player->prev_mouse_x = x;
	player->p_angle += (delta_x * MOUSE_SENSITIVITY);

	if (player->p_angle < 0)
		player->p_angle += _2PI;
	else if (player->p_angle > _2PI)
		player->p_angle -= _2PI;
	return (0);
}
