#ifndef CUB3D_H
# define CUB3D_H

# include "../includes/libft/libft.h"
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

typedef struct s_enemy
{
	int				type;
	int				rot;
	t_point			pos;
	float			p_angle;
	int				look_dir;
	int				speed;
	int				shooting;
}					t_enemy;

typedef struct	s_map
{
	char			**map;
	int				rows;
	int				cols;
	t_point_i		player;
	struct s_enemy	**enemies;
	int				enemy_count;
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
	int				width;
	int				height;
}					t_img;

typedef struct s_textures
{
	struct s_img	north;
	struct s_img	south;
	struct s_img	east;
	struct s_img	west;
	struct s_img	weapon[4][5];
}					t_textures;

typedef struct	s_game
{
	void				*mlx;
	void				*win;
	void				*mapwin;
	char				**pixel_map;
	struct s_map		*map;
	struct s_img		img;
	struct s_img		mapimg;
	int					width;
	int					height;
	struct s_player		*player;
	int					dir;
	struct s_textures	*textures;
	int					f_color;
	int					c_color;
	int					color;
	float				fraction_x;
	float				fraction_y;
	struct s_enemy		**enemies;
	int					enemy_count;
}						t_game;

typedef struct s_player
{
	int				up_down;
	int				left_right;
	int				rot;
	t_point			pos;
	float			p_angle;
	int				look_dir;
	int				speed;
	float			jump_height;
	bool			jumping;
	bool			jump_peak;
	int				shooting;
	int				weapon;
}					t_player;

typedef struct s_raycaster
{
	t_point		dir;
	t_point		scalingf;
	t_point		ray_len;
	t_point_i	map_loc;
	t_point_i	map_step;
	float		len;
	t_point		intersection;
	t_point		start;
	bool		wall;
}					t_raycaster;


typedef struct s_minimap
{
	t_point			start;
	t_point			start_map;
	t_point			end_map;
	t_point			pos_player;
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
bool	surrounded_by_walls2(t_map *map);
bool	valid_upside(t_map *map, int *coll, int *row, bool *last_dir);
bool	valid_rightside(t_map *map, int *coll, int *row, bool *last_dir);
bool	valid_downside(t_map *map, int *coll, int *row, bool *last_dir);
bool	valid_leftside(t_map *map, int *coll, int *row, bool *last_dir);
void	fill_with_space(t_map *map);

/* ------------------------------- Mlx Init -------------------------------- */
/* ------------------------------------------------------------------------- */
void	start_game(t_map *map);
void	init_mlx(t_game *game, t_textures *textures, t_player *player, t_map *map);
void	init_game_struct(t_game *game, t_player *player, t_map *map);
void	init_window(t_game *game, t_map *map);
void	init_image(t_game *game);
void	init_events(t_game *game);
int		key_press(int keysym, t_game *game);
int		key_release(int keysym, t_game *game);
int		mouse_hook(int button, int x, int y, t_game *game);
int		convert(t_rgb color);
void	init_textures(t_game *game, t_textures *textures);

/* ------------------------------- Rendering ------------------------------- */
/* ------------------------------------------------------------------------- */
void	render_2dgame(t_game *game);
int		render(t_game *game);
void	render_image(t_game *game, int start_x, int start_y, int color);
void	put_pixel_to_img(t_game *game, int x, int y, int color);
void	draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color);
void	move_player(t_game *game, float move_x, float move_y);
void	check_movements(t_game *game);
void	put_pixel_to_mapimg(t_game *game, int x, int y, int color);
void	draw_vline(t_game *game, int start_x, int start_y, int end_x, int end_y, int color);
int		get_texture_color(t_game *game, int tex_x, int tex_y);
void	draw_textures(t_game *game, int start_x, int start_y, int end_x, int end_y);
void	jumping(t_player *player);

/* --------------------------- Weapon Rendering ---------------------------- */
/* ------------------------------------------------------------------------- */
void	draw_weapon(t_game *game, int frame);
int		get_weapon_color(t_game *game, int tex_x, int tex_y, int frame);
void	render_weapon(t_game *game);

/* ------------------------------ Ray Caster ------------------------------- */
/* ------------------------------------------------------------------------- */
void	init_ray(t_raycaster *ray, t_player *player, float angle);
float	cast_ray(t_game *game, float angle);
void	raycast(t_game *game);

/* ------------------------------- Movements ------------------------------- */
/* ------------------------------------------------------------------------- */
void	rotate_player(t_player *player);
void	jumping(t_player *player);
void	move_player(t_game *game, float new_x, float new_y);
void	check_movements(t_game *game);

/* ------------------------------- Mini Map -------------------------------- */
/* ------------------------------------------------------------------------- */
void	minimap(t_game *game);
void	render_minimap(t_game *game, int start_x, int start_y, int color);

/* -------------------------------- Utils ---------------------------------- */
/* ------------------------------------------------------------------------- */
void	print_textures(t_map *map_info);
void	print_map(char **map);
void	print_pixel_map(t_game *game);

/* ----------------------------- Close Program ----------------------------- */
/* ------------------------------------------------------------------------- */
void	error_message(char *str);
void	free_map(t_map *map, char *str, int status);
int		close_window(t_game *game, int status, int exit);

#endif
