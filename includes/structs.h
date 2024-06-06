#ifndef STRUCTS_H
# define STRUCTS_H

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
	int				width;
	int				height;
}					t_img;

typedef struct s_textures
{
	struct s_img	north;
	struct s_img	south;
	struct s_img	east;
	struct s_img	west;
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
	int				prev_mouse_x;
	int				prev_mouse_y;
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

#endif
