#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
// # include "./minilibx-mac/mlx.h"
# include "./minilibx-linux/mlx.h"
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

// Linux
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define LEFT 65361
# define RIGHT 65363
# define DOWN 65364

// // Mac
// # define ESC 53
// # define W 13
// # define A 0
// # define S 1
// # define D 2
// # define UP 126
// # define LEFT 123
// # define RIGHT 124
// # define DOWN 125

# define WHITESPACE " \t\n\r\f\v"
# define VALID_CHARS "NSEW01 \t\n\r\f\v\0"
# define WS_COMMA " \t\n\r\f\v,"

# define NORTH 78
# define SOUTH 83
# define EAST 69
# define WEST 87

# define PLAYER "NSEW"
# define WALL 49
# define VISITED 85
# define ENEMY 88
# define EMPTY 48
# define WON 89
# define SCALE 50
# define PSIZE 15
# define WIDTH 1080
# define HEIGHT 720

#ifndef PI
# define PI 3.141592653
#endif

# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define BLACK 0x000000

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
	int				max_coll;
	int				player_y;	//maybe use different variable type
	int				player_dir;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	struct s_rgb	f_color;
	struct s_rgb	c_color;

}					t_map;

typedef struct s_img
{
	void			*img_ptr;
	char			*pixels_ptr;
	int				bits_per_pixel;
	int				endian;
	int				line_len;
}					t_img;

typedef struct	s_game
{
	void			*mlx;
	void			*win;
	struct s_map	*map;
	struct s_img	img;
	int				width;
	int				height;
	float			player_x;
	float			player_y;
	float			player_angle;
}					t_game;

typedef struct s_player
{

}			t_player;

/* ------------------------------- Read Input ------------------------------ */
void	read_input(int argc, char *argv[], t_map *map);
void	check_arguments(int argc, char *argv[]);
bool	is_cub(char *file);
void	read_textures(t_map *map, int fd);
void	read_map(t_map *map, int fd);
void	remove_extra_rows(t_map *map, int rows, char **temp);
void	get_texture(char *line, char type, t_map *map);
void	assign_color(int i, char *num, char type, t_map *map);
void	get_color(char *line, char type, t_map *map);
bool	assigned_all(t_map *map);
void	init_map(t_map *map);

/* ----------------------------- Validade map ------------------------------ */
void	validate_map(t_map *map);
bool	valid_color(int color);
bool	invalid_color(t_map *map);
bool	map_split(t_map *map);
void	get_player_coordinates(t_map *map, int rows, int coll);
bool	invalid_characters(t_map *map);
bool	found_leaking_space(t_map *map, int row, int coll);
bool	leaking_empty_spaces(t_map *map);
bool	surrounded_by_walls(t_map *map);
bool	valid_upside(t_map *map, int *coll, int *row, bool *last_dir);
bool	valid_rightside(t_map *map, int *coll, int *row, bool *last_dir);
bool	valid_downside(t_map *map, int *coll, int *row, bool *last_dir);
bool	valid_leftside(t_map *map, int *coll, int *row, bool *last_dir);
void	fill_with_space(t_map *map);

/* ------------------------------- Mlx Init -------------------------------- */
void	start_game(t_map *map);
int		close_window(t_game *game, int status, int exit);
int		key_press(int keysym, t_game *game);
int		mouse_hook(int button, int x, int y, t_game *game);
void	init_mlx(t_game *game, t_map *map);


/* ------------------------------- Rendering ------------------------------- */
void	draw_player(t_game *game, int start_x, int start_y, int width, int height, int color);
void	render_2dgame(t_game *game);

/* -------------------------------- Utils ---------------------------------- */
void	print_textures(t_map *map_info);
void	print_map(t_map map);

/* ----------------------------- Close Program ----------------------------- */
void	error_message(char *str);
void	free_map(t_map *map, char *str, int status);
int		close_window(t_game *game, int status, int exit);

#endif
