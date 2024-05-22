#include "../includes/cub3d.h"

void	error_message(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit (1);
}

void	free_map(t_map *map, char *str, int status)
{
	int	row;

	row = 0;
	while (map->map[row])
		free(map->map[row++]);
	free(map->map);
	if (status)
		error_message(str);
	else
	{
		ft_printf("%s\n", str);
		exit (0);
	}
}
