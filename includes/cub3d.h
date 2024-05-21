#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <stdio.h>

# define NORTH 80
# define SOUTH 81
# define EAST 82
# define WEAST 83

# define WALL 49
# define ENEMY 88
# define EMPTY 48
# define WON 87
# define SCALE 50

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define RIGHT 65363
# define DOWN 65364

# define WHITESPACE " /t/r/v"

typedef struct	s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct	s_map
{
	char			**map;
	int				rows;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	struct s_rgb	*color

}					t_map;

typedef struct s_player
{

}			t_player;

#endif
