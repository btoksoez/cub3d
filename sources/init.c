#include "../includes/cub3d.h"

void init_map(t_map *map)
{
	if (map == NULL)
		return;
	map->map = NULL;
	map->rows = 0;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->f_color.red = -1;
	map->f_color.green = -1;
	map->f_color.blue = -1;
	map->c_color.red = -1;
	map->c_color.green = -1;
	map->c_color.blue = -1;
}
