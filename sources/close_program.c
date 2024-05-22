#include "../includes/cub3d.h"

void	error_message(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit (1);
}

void	free_map(t_map *map, char *str, int status)
{
	int	rows;

	rows = 0;
	while (map->map[rows])
	{
		if (map->map[rows])
			free(map->map[rows]);
		rows++;
	}
	if (map->map)
		free(map->map);
	if (status)
		error_message(str);
	else
	{
		ft_printf("%s\n", str);
		exit (0);
	}
}
