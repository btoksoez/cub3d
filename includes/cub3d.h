#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>

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

# define WHITESPACE " \t\n\r\f\v"
# define WS_COMMA " \t\n\r\f\v,"

# define WIDTH 1080
# define HEIGHT 720

# define TILE_SIZE 64

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
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	struct s_rgb	f_color;
	struct s_rgb	c_color;

}					t_map;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}			t_img;

typedef struct	s_game
{
	void			*mlx;
	void			*win;
	struct s_map	*map;
	struct s_img	img;
}				t_game;

typedef struct s_player
{

}			t_player;

/* ------- init ------ */
void	init_map(t_map *map);
void	init_window(t_game *game, t_map *map);
void	init_images();
void	init_events(t_game *game);
void	init_mlx(t_game *game, t_map *map);

/*	------ utils -------- */
char	*ft_strdup_delimiter(const char *s, char *delimiter);
bool	ft_isdigit_str(char *str);
void	print_map(t_map *map_info);
void	skip_whitespace(char **line);
void	error_message(char *str);

/* ----- parsing ------- */
void	read_input(int argc, char *argv[], t_map *map);

/* ------ events ------- */
int		key_press(int keysym, t_game *game);
int		mouse_hook(int button, int x, int y, t_game *game);
int		close_window(t_game *game);

/* ------ start game ------ */
void	start_game(t_map *map);



#endif
