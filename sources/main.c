#include "../includes/cub3d.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	read_input(argc, argv, &map);
	char *map_array[10] = {
		"0101010101",
		"1010101010",
		"0101010101",
		"1010101010",
		"0101010101",
		"1010101010",
		"0101010101",
		"1010101010",
		"0101010101",
		"1010101010"
	};
	map.map = map_array;
	start_game(&map);
	// clean_up();
	return (0);
}
