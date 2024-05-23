#include "../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	// read_input(argc, argv, &map);

	//testing
	char *map_array[10] = {
		"1000000101",
		"1010101010",
		"0101010101",
		"1010101010",
		"0101010101",
		"1010101010",
		"0101010101",
		"1010101010",
		"1101010101",
		NULL
	};
	(void)argc;
	(void)argv;
	map.map = map_array;
	//testing

	start_game(&map);
	// clean_up();
	return (0);
}
