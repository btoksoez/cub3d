#include "../includes/cub3d.h"

char	*ft_strdup_delimiter(const char *s, char *delimiter)
{
	int		i;
	char	*dup;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && !ft_strchr(delimiter, s[i]));
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		((unsigned char *)dup)[i] = ((unsigned char *)s)[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}


