#include "../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_map map;

	init_map(&map);
	read_input(argc, argv, &map);

	// print_textures(&map);
	print_map(map);
	// init();
	// clean_up();
	return (0);
}