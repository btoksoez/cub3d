#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"

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

/* ------------------------------ Ray Caster ------------------------------- */
/* ------------------------------------------------------------------------- */
void	init_ray(t_raycaster *ray, t_player *player, float angle);
float	cast_ray(t_game *game, float angle, t_raycaster *ray);
void	raycast(t_game *game, t_raycaster *ray);
void	cast_2d_rays(t_game *game, t_raycaster *ray, int hori_vision, int vert_vision);
void	cast_2d_ray(t_game *game, float angle, t_raycaster *ray, int hori_vision, int vert_vision);
void	init_2d_ray(t_raycaster *ray, t_player *player, float angle);

/* ------------------------------- Movements ------------------------------- */
/* ------------------------------------------------------------------------- */
void	rotate_player(t_player *player);
void	jumping(t_player *player);
void	move_player(t_game *game, float new_x, float new_y);
void	check_movements(t_game *game);
int		mouse_hook(int x, t_player *player);

/* ------------------------------- Mini Map -------------------------------- */
/* ------------------------------------------------------------------------- */
void	minimap(t_game *game, t_raycaster *ray);
void	render_player(t_game *game, int start_x, int start_y);

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
