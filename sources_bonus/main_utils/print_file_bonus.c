#include "../../includes_bonus/cub3d.h"

void	print_textures(t_map *map_info)
{
	printf("\n");
	printf("North Texture: %s\n", map_info->no_texture);
	printf("South Texture: %s\n", map_info->so_texture);
	printf("West Texture: %s\n", map_info->we_texture);
	printf("East Texture: %s\n", map_info->ea_texture);
	printf("Floor Color: R=%d, G=%d, B=%d\n", map_info->f_color.red,
		map_info->f_color.green, map_info->f_color.blue);
	printf("Ceiling Color: R=%d, G=%d, B=%d\n", map_info->c_color.red,
		map_info->c_color.green, map_info->c_color.blue);
	printf("\n");
}

void	print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == ' ')
				printf(" ");
			else
				printf("%c", map[i][j]);
			j++;
		}
		if (map[i][j] == '\0')
			printf(" - This row is null-terminated.\n");
		else
			printf(" - This row is not null-terminated.\n");
		i++;
	}
	if (map[i] == NULL)
		printf("The last row is NULL.\n");
	else
		printf("The last row is not NULL.\n");
	printf("\n\n\n");
}

void	print_pixel_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->pixel_map[i])
	{
		printf("%s\n", game->pixel_map[i]);
		i++;
	}
}
