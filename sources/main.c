#include "../includes/cub3d.h"

static void	print_map2(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (map.map[i])
	{
		j = 0;
		while (map.map[i][j])
		{
			printf("%c", map.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_map map;

	init_map(&map);
	read_input(argc, argv, &map);
	print_map2(map);
	// init();
	// clean_up();
	return (0);
}
