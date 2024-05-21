#include "../includes/cub3d.h"

char	*ft_strdup_delimiter(const char *s, char *delimiter)
{
	int		i;
	char	*dup;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && !ft_strchr(delimiter, s[i]))
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i] && !ft_strchr(delimiter, s[i]))
	{
		((unsigned char *)dup)[i] = ((unsigned char *)s)[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

bool	ft_isdigit_str(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	skip_whitespace(char **line)
{
	if (**line == '\0')
		return ;
	while (ft_strchr(WHITESPACE, **line))
		(*line)++;
}

void print_map(t_map *map_info)
{
    // Print the map grid
    printf("---- Map ----\n");
    for (int i = 0; i < map_info->rows; i++) {
        printf("%s\n", map_info->map[i]);
    }

    // Print the texture paths
    printf("North Texture: %s\n", map_info->no_texture);
    printf("South Texture: %s\n", map_info->so_texture);
    printf("West Texture: %s\n", map_info->we_texture);
    printf("East Texture: %s\n", map_info->ea_texture);

    // Print the floor and ceiling colors
    printf("Floor Color: R=%d, G=%d, B=%d\n", map_info->f_color.red, map_info->f_color.green, map_info->f_color.blue);
    printf("Ceiling Color: R=%d, G=%d, B=%d\n", map_info->c_color.red, map_info->c_color.green, map_info->c_color.blue);
	printf("\n\n\n");
}




