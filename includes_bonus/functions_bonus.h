#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs_bonus.h"

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
int		mouse_hook(int x, t_player *player);
int		convert(t_rgb color);
void	init_textures(t_game *game, t_textures *textures);

/* ------------------------------- Rendering ------------------------------- */
/* ------------------------------------------------------------------------- */
int		render(t_game *game);
void	put_pixel_to_img(t_game *game, int x, int y, int color);
void	draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color);
void	move_player(t_game *game, float move_x, float move_y);
void	check_movements(t_game *game);
void	draw_vline(t_game *game, int start_x, int start_y, int end_x, int end_y, int color);
int		get_texture_color(t_game *game, int tex_x, int tex_y);
void	draw_textures(t_game *game, int start_x, int start_y, int end_x, int end_y);
void	jumping(t_player *player);

/* --------------------------- Weapon Rendering ---------------------------- */
/* ------------------------------------------------------------------------- */
void	draw_weapon(t_game *game, int frame);
int		get_weapon_color(t_game *game, int tex_x, int tex_y, int frame);
void	render_weapon(t_game *game);

/* --------------------------- Sprite Rendering ---------------------------- */
/* ------------------------------------------------------------------------- */
// void	render_sprites(t_game *game);
void	get_enemy_distance(t_raycaster *ray, t_game *game);
t_point	get_normalized_vector(t_point p1, t_point p2);
void	get_enemy_positions(t_game *game);
void	draw_enemy(t_game *game, int x, t_raycaster *ray);
void	animate_sprites(t_game *game);
void	move_sprites(t_game *game);

/* ------------------------------ Ray Caster ------------------------------- */
/* ------------------------------------------------------------------------- */
void	init_ray(t_raycaster *ray, t_player *player, float angle);
float	cast_ray(t_raycaster *ray, t_game *game, float angle);
void	raycast(t_game *game, t_raycaster *ray);
void	check_direction(t_game *game, t_raycaster *ray, int visited);

/* ------------------------------- Movements ------------------------------- */
/* ------------------------------------------------------------------------- */
void	rotate_player(t_player *player);
void	jumping(t_player *player);
void	move_player(t_game *game, float new_x, float new_y);
void	check_movements(t_game *game);

/* ------------------------------- Mini Map -------------------------------- */
/* ------------------------------------------------------------------------- */
void	minimap(t_game *game, t_raycaster *ray);
void	init_minimap(t_player *player, t_minimap *mini);
void	render_player_and_rays(t_game *game, t_raycaster *ray, t_minimap mini);
void	render_player(t_game *game, int start_x, int start_y);
void	raycast_2d(t_game *game, t_raycaster *ray, t_minimap mini);
void	cast_2d_ray(t_game *game, float angle, t_raycaster *ray, t_minimap mini);
void	init_2d_ray(t_raycaster *ray, t_player *player, float angle);
void	adjust_raylen(t_raycaster *ray, float angle, t_minimap mini, t_player *player);
void	draw_ray(t_game *game, t_player *player, t_raycaster *ray, t_minimap mini);
void	draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color);
void	get_start_x(t_player *player, t_minimap *mini);

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
void	player_dead(t_game *game);


#endif
