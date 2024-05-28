#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "define.h"
// # include <X11/keysym.h>
// # include <X11/X.h>

/* -------------------------------- Structs -------------------------------- */
/* ------------------------------------------------------------------------- */
typedef struct	s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct s_point
{
	float			x;
	float			y;
}					t_point;

typedef struct s_point_i
{
	int				x;
	int				y;
}					t_point_i;

typedef struct	s_map
{
	char			**map;
	int				rows;
	int				cols;
	t_point			player;
	float			player_dir;
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
	char			**pixel_map;
	struct s_map	*map;
	struct s_img	img;
	int				width;
	int				height;
	struct s_player	*player;
}					t_game;

typedef struct s_player
{
	int				up_down;
	int				left_right;
	int				rot;
	t_point			pos;
	float			p_angle;
	int				look_dir;
}					t_player;

typedef struct s_raycaster
{
	t_point		dir;
	t_point		stepsize;
	t_point_i	tile_map;
	t_point		ray_len;
	t_point_i	step;
	float		len;
	t_point		intersection;
	float 		next_grid_x;
	float 		next_grid_y;
	float		slope;
	float		intercept_y_axis;
	t_point		hit_grid_x;
	t_point		hit_grid_y;
	t_point		dist_to_grid;
	bool		wall;
	t_point		current_pos;
}					t_raycaster;


typedef struct s_minimap
{
	t_point_i		start;
	t_point_i		start_map;
	t_point_i		end_map;
	t_point_i		pos_player;
}					t_minimap;

/* ------------------------------- Read Input ------------------------------ */
/* ------------------------------------------------------------------------- */
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

/* ----------------------------- Validate map ------------------------------ */
/* ------------------------------------------------------------------------- */
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
/* ------------------------------------------------------------------------- */
void	start_game(t_map *map);
void	init_mlx(t_game *game, t_player *player, t_map *map);
void	init_game_struct(t_game *game, t_player *player, t_map *map);
void	init_window(t_game *game, t_map *map);
void	init_image(t_game *game);
void	init_events(t_game *game);
int		key_press(int keysym, t_game *game);
int		key_release(int keysym, t_game *game);
int		mouse_hook(int button, int x, int y, t_game *game);

/* ------------------------------- Rendering ------------------------------- */
/* ------------------------------------------------------------------------- */
void	render_2dgame(t_game *game);
int		render(t_game *game);
void	render_image(t_game *game, int start_x, int start_y, int color);
void	put_pixel_to_img(t_game *game, int x, int y, int color);
void	draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color);
void	move_player(t_game *game, float move_x, float move_y);
void	hook_player(t_game *game);
void	draw_point(t_game *game, int x, int y, int color);

/* ------------------------------ Ray Caster ------------------------------- */
/* ------------------------------------------------------------------------- */
void	cast_rays(t_game *game);

/* ------------------------------- Mini Map -------------------------------- */
/* ------------------------------------------------------------------------- */
void	minimap(t_game *game);
void	render_minimap(t_game *game, int start_x, int start_y, int color);

/* -------------------------------- Utils ---------------------------------- */
/* ------------------------------------------------------------------------- */
void	print_textures(t_map *map_info);
void	print_map(t_map map);
void	print_pixel_map(t_game *game);

/* ----------------------------- Close Program ----------------------------- */
/* ------------------------------------------------------------------------- */
void	error_message(char *str);
void	free_map(t_map *map, char *str, int status);
int		close_window(t_game *game, int status, int exit);

#endif
