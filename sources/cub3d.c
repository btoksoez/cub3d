#include "../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	init_map(&map);
	read_input(argc, argv, &map);
	start_game(&map);
	return (0);
}
