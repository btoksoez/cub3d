#include "../../includes/cub3d.h"

void	print_textures(t_map *map_info)
{
	printf("\n");
	printf("North Texture: %s\n", map_info->no_texture);
	printf("South Texture: %s\n", map_info->so_texture);
	printf("West Texture: %s\n", map_info->we_texture);
	printf("East Texture: %s\n", map_info->ea_texture);
	printf("Floor Color: R=%d, G=%d, B=%d\n", map_info->f_color.red, map_info->f_color.green, map_info->f_color.blue);
	printf("Ceiling Color: R=%d, G=%d, B=%d\n", map_info->c_color.red, map_info->c_color.green, map_info->c_color.blue);
	printf("\n");
}

void	print_map(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (map.map[i])
	{
		j = 0;
		while (map.map[i][j])
		{
			if (map.map[i][j] == ' ')
				printf(" ");
			else
				printf("%c", map.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
