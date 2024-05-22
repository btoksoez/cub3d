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
# define VISITED 85
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

# define WHITESPACE " \t\n\r\f\v"
# define VALID_CHARS "NSEW01 \t\n\r\f\v\0"
# define WS_COMMA " \t\n\r\f\v,"

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
	int				player_x;
	int				player_y;
	bool			valid;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	struct s_rgb	f_color;
	struct s_rgb	c_color;

}					t_map;

typedef struct s_player
{

}			t_player;

/* ------------------------------- Read Input ------------------------------ */
void	read_input(int argc, char *argv[], t_map *map);
void	check_arguments(int argc, char *argv[]);
bool	is_cub(char *file);
void	read_textures(t_map *map, int fd);
void	read_map(t_map *map, int fd);
void	get_texture(char *line, char type, t_map *map);
void	assign_color(int i, char *num, char type, t_map *map);
void	get_color(char *line, char type, t_map *map);
bool	assigned_all(t_map *map);

/* ----------------------------- Validade map ------------------------------ */
void	validate_map(t_map *map);
bool	valid_color(int color);
bool	invalid_color(t_map *map);
bool	map_split(t_map *map);

/* ------------------------------- Mlx Init -------------------------------- */
void	init_map(t_map *map);

/* -------------------------------- Utils ---------------------------------- */
void	print_textures(t_map *map_info);
void	print_map(t_map map);

/* ----------------------------- Close Program ----------------------------- */
void	error_message(char *str);
void	free_map(t_map *map, char *str, int status);

#endif
