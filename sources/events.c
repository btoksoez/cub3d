#include "../includes/cub3d.h"

int	key_press(int keysym, t_game *game)
{
	printf("Pressed key: %d\n", keysym);
	if (keysym == XK_Escape || keysym == 53)
		close_window(game);
	//add WDAS, ARROWS, shooting, space, reload ...
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

int	close_window(t_game *game)
{
	ft_printf("Closing Window");
	//mlx_destroy_image(game->mlx, );
	mlx_destroy_window(game->mlx, game->win);
	// mlx_destroy_display(game->mlx);	//add for linux
	free(game->mlx);
	exit(1);
}
