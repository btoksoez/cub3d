#include "../../includes_bonus/cub3d.h"

void	error_message(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit (1);
}

int	close_window(t_game *game, int status, int exit)
{
	mlx_destroy_window(game->mlx, game->win);
	// mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (exit == WON)
		free_map(game->map, "You Won!", status);
	else
		free_map(game->map, "Game Over!", status);
	return (0);
}

void	free_map(t_map *map, char *str, int status)
{
	// we should add the mlx here
	int	rows;

	rows = 0;
	if (map->map)
	{
		while (map->map[rows])
		{
			if (map->map[rows])
				free(map->map[rows]);
			rows++;
		}
		free(map->map);
	}
	//add freeing texture strings
	if (status)
		error_message(str);
	else
	{
		ft_printf("%s\n", str);
		exit (0);
	}
}