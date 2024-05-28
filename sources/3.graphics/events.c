#include "../../includes/cub3d.h"

/* checks whether move is possible and calculates new player->pos.x/y with given move X/Y*/
void	move_player(t_game *game, float new_x, float new_y)
{
	// int			x;
	// int			y;
	t_player	*player;

	player = game->player;
	// x = player->pos.x;
	// y = player->pos.y;
	if (game->pixel_map[(int)(new_y)][(int)new_x] != WALL
		&& game->pixel_map[(int)(new_y + PSIZE)][((int)new_x + PSIZE)] != WALL
		&& game->pixel_map[(int)(new_y + PSIZE)][(int)new_x] != WALL
		&& game->pixel_map[(int)(new_y)][((int)new_x + PSIZE)] != WALL)
		//maybe add margin for the wall
		{
			player->pos.y = new_y;
			player->pos.x = new_x;
		}
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
