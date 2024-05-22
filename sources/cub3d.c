#include "../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_map map;

	init_map(&map);
	read_input(argc, argv, &map);
	start_game(&map);

	// print_textures(&map);
	// print_map(map);
	// clean_up();
	return (0);
}
