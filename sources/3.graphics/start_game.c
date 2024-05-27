#include "../../includes/cub3d.h"

void	start_game(t_map *map)
{
	t_game		game;
	t_player	player;

	init_mlx(&game, &player, map);
	mlx_loop_hook(game.mlx, &render, &game);
	mlx_loop(game.mlx);
}

void	rotate_player(t_player *player)
{
	if (player->rot == LEFT)
	{
		player->p_angle -= ROT_SPEED;
		if (player->p_angle < 0)
			player->p_angle += 2 * PI;
	}
	if (player->rot == RIGHT)
	{
		player->p_angle += ROT_SPEED;
		if (player->p_angle > 2 * PI)
			player->p_angle -= 2 * PI;
	}
}

/* this should calculate the move based on flags and call move and rotoate functions */
void	hook_player(t_game *game)
{
	t_player	*player;
	float		new_x;
	float		new_y;

	player = game->player;
	new_x = player->pos_x;
	new_y = player->pos_y;
	rotate_player(player);
	if (player->up_down == UP)
	{
		new_x = player->pos_x + (MOVE * cos(player->p_angle));
		new_y = player->pos_y + (MOVE * sin(player->p_angle));
	}
	if (player->up_down == DOWN)
	{
		new_x = player->pos_x + (MOVE * cos(player->p_angle + PI));
		new_y = player->pos_y + (MOVE * sin(player->p_angle + PI));
	}
	if (player->left_right == LEFT)
	{
		new_x = player->pos_x + (MOVE * cos(player->p_angle - PI_05));
		new_y = player->pos_y + (MOVE * sin(player->p_angle - PI_05));
	}
	if (player->left_right == RIGHT)
	{
		new_x = player->pos_x + (MOVE * cos(player->p_angle + PI_05));
		new_y = player->pos_y + (MOVE * sin(player->p_angle + PI_05));
	}
	move_player(game, new_x, new_y);
}

void	init_raycaster(t_raycaster *ray, t_player *player)
{
	ray->x = 0;
	ray->y = 0;
	ray->next_grid_x = 0;
	ray->next_grid_y = 0;
	ray->slope = 0;
	ray->intercept_y_axis = 0;
	ray->current_pos_x = player->pos_x;
	ray->current_pos_y = player->pos_y;
	ray->hit_x_hori = 0;
	ray->hit_y_hori = 0;
	ray->hit_x_vert = 0;
	ray->hit_y_vert = 0;
	ray->dist_to_grid_y = 0;
	ray->dist_to_grid_x = 0;
	ray->wall = false;
}

void	get_next_grid(t_player *player, t_raycaster *ray)
{
	if (ray->current_pos_x == player->pos_x && ray->current_pos_y == player->pos_y)
	{
		if (player->p_angle < 2 * PI && player->p_angle >= PI)
			ray->next_grid_y = floorf(ray->current_pos_y / SCALE) * SCALE;
		else
			ray->next_grid_y = ceilf(ray->current_pos_y / SCALE) * SCALE;
		if (player->p_angle < PI_15 && player->p_angle >= PI_05)
			ray->next_grid_x = floorf(ray->current_pos_x / SCALE) * SCALE;
		else
			ray->next_grid_x = ceilf(ray->current_pos_x / SCALE) * SCALE;
	}
	else
	{
		if (player->p_angle < 2 * PI && player->p_angle >= PI)
			ray->next_grid_y = floorf((ray->current_pos_y - 1) / SCALE) * SCALE;
		else
			ray->next_grid_y = ceilf((ray->current_pos_y + 1) / SCALE) * SCALE;
		if (player->p_angle < PI_15 && player->p_angle >= PI_05)
			ray->next_grid_x = floorf((ray->current_pos_x - 1) / SCALE) * SCALE;
		else
			ray->next_grid_x = ceilf((ray->current_pos_x + 1) / SCALE) * SCALE;
	}
	printf("next grid Y: %f. next grid x: %f\n", ray->next_grid_y, ray->next_grid_x);
}

void	get_grid_ray_intersection(t_player *player, t_raycaster *ray)
{
	// get a second point to get a line
	ray->x = player->pos_x + PCENTER + (SCALE * cos(player->p_angle));
	ray->y = player->pos_y + PCENTER + (SCALE * sin(player->p_angle));

	// m
	ray->slope = (ray->y - (player->pos_y + PCENTER)) / (ray->x - (player->pos_x + PCENTER));
	if (ray->slope == 0)
		ray->slope = 1e-6f;

	// c = y - mx
	ray->intercept_y_axis = (player->pos_y + PCENTER) - (ray->slope * (player->pos_x + PCENTER));

	// point at which the rayline intercepts (x,y) in the Y axis
	ray->hit_x_hori = (ray->next_grid_y - ray->intercept_y_axis) / ray->slope;
	ray->hit_y_hori = ray->slope * ray->hit_x_hori + ray->intercept_y_axis;


	// point at which the rayline intercepts (x,y) in the X axis
	ray->hit_x_vert = ray->next_grid_x;
	ray->hit_y_vert = ray->slope * ray->hit_x_vert + ray->intercept_y_axis;

	printf("hit_x_hori: %f\n hit_y_hori: %f\n", ray->hit_x_hori, ray->hit_y_hori);
	printf("hit_x_vert: %f\n hit_y_vert: %f\n", ray->hit_x_vert, ray->hit_y_vert);

}

//vert is x

void	get_distance_to_grid(t_player *player, t_raycaster *ray, t_game *game)
{
	if (player->p_angle > 0 && player->p_angle <= PI_05)	//looking south east
	{
		ray->dist_to_grid_y = fabs(player->pos_y - ray->next_grid_y) / cos(fabs(PI_05 - player->p_angle));
		ray->dist_to_grid_x = fabs(player->pos_x - ray->next_grid_x) / cos(fabs(player->p_angle));
		player->look_dir = SE;
	}
	if (player->p_angle > PI_05 && player->p_angle <= PI)	//looking south west
	{
		ray->dist_to_grid_y = fabs(player->pos_y - ray->next_grid_y) / cos(fabs(player->p_angle - PI_05));
		ray->dist_to_grid_x = fabs(player->pos_x - ray->next_grid_x) / cos(fabs(PI - player->p_angle));
		player->look_dir = SW;
	}
	if (player->p_angle > PI && player->p_angle <= PI_15)	//looking north west
	{
		ray->dist_to_grid_y = fabs(player->pos_y - ray->next_grid_y) / cos(fabs(PI_15 - player->p_angle));
		ray->dist_to_grid_x = fabs(player->pos_x - ray->next_grid_x) / cos(fabs(player->p_angle - PI));
		player->look_dir = NW;
	}
	if (player->p_angle > PI_15 && player->p_angle <= 2 * PI)	//looking north east
	{
		ray->dist_to_grid_y = fabs(player->pos_y - ray->next_grid_y) / cos(fabs(player->p_angle - PI_15));
		ray->dist_to_grid_x = fabs(player->pos_x - ray->next_grid_x) / cos(fabs(2 * PI - player->p_angle));
		player->look_dir = NE;
	}
	if (fabs(ray->dist_to_grid_y) > SCALE * game->map->max_coll)
		ray->dist_to_grid_y = SCALE * game->map->max_coll;
	if (fabs(ray->dist_to_grid_x) > SCALE * game->map->rows)
		ray->dist_to_grid_x = SCALE * game->map->rows;
}

bool	is_wall(t_player *player, t_raycaster *ray, t_game *game)
{
	if (ray->dist_to_grid_y < ray->dist_to_grid_x)
	{
		ray->current_pos_x = ray->hit_x_hori;
		ray->current_pos_y = ray->hit_y_hori;
		if (player->look_dir == NE || player->look_dir == NW)
		{
			if (game->map->map[(int)ray->hit_y_hori / SCALE - 1][(int)ray->hit_x_hori / SCALE] != EMPTY)
				return (draw_line(game, player->pos_x + PCENTER, player->pos_y + PCENTER, ray->current_pos_x, ray->current_pos_y, BLUE), true);
		}
		else if (game->map->map[(int)ray->hit_y_hori / SCALE][(int)ray->hit_x_hori / SCALE] != EMPTY)
			return (draw_line(game, player->pos_x + PCENTER, player->pos_y + PCENTER, ray->current_pos_x, ray->current_pos_y, BLUE), true); //after stop, send this to raycaster
	}
	else if (ray->dist_to_grid_y >= ray->dist_to_grid_x)
	{
		ray->current_pos_x = ray->hit_x_vert;
		ray->current_pos_y = ray->hit_y_vert;
		if (player->look_dir == NW || player->look_dir == SW)
		{
			if (game->map->map[(int)ray->hit_y_vert / SCALE][(int)ray->hit_x_vert / SCALE - 1] != EMPTY)
				return (draw_line(game, player->pos_x + PCENTER, player->pos_y + PCENTER, ray->hit_x_vert, ray->hit_y_vert, BLUE), true);
		}
		else if (game->map->map[(int)ray->hit_y_vert / SCALE][(int)ray->hit_x_vert / SCALE] != EMPTY)
			return (draw_line(game, player->pos_x + PCENTER, player->pos_y + PCENTER, ray->hit_x_vert, ray->hit_y_vert, BLUE), true); //after stop, send this to raycaster
	}
	return (false);
}

void	cast_rays(t_game *game)
{
	t_player	*player;
	t_raycaster	ray;

	player = game->player;
	init_raycaster(&ray, player);
	while (true)
	{
		get_next_grid(player, &ray);
		get_grid_ray_intersection(player, &ray);
		get_distance_to_grid(player, &ray, game);
		if (is_wall(player, &ray, game))
			break ;
	}

	// if (rx % SCALE != 0)

	// ry = player->pos_y + (MOVE * sin(player->p_angle));
	// game->map->map[(int)(new_y) / SCALE][(int)new_x / SCALE] != WALL
	// 	&& game->map->map[(int)(new_y + PSIZE) / SCALE][((int)new_x + PSIZE) / SCALE] != WALL
	// 	&& game->map->map[(int)(new_y + PSIZE) / SCALE][(int)new_x / SCALE] != WALL
	// 	&& game->map->map[(int)(new_y) / SCALE][((int)new_x + PSIZE) / SCALE] != WALL)
}

int	render(t_game *game)
{
	// delete_image?
	hook_player(game);	//sets new pos of player based on u_d, l_r
	render_2dgame(game);
	cast_rays(game);
	// minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}

void	render_2dgame(t_game *game)
{
	int			y;
	int			x;
	t_player	*player;

	player = game->player;
	y = 0;
	render_image(game, 0, 0, SCREEN);
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->max_coll)
		{
			if (game->map->map[y][x] == WALL)
				render_image(game, x * SCALE, y * SCALE, WALLS);
			if (game->map->map[y][x] == EMPTY)
				render_image(game, x * SCALE, y * SCALE, SPACE);
			render_image(game, player->pos_x, player->pos_y, PLAYER_);
			x++;
		}
		y++;
	}
}
// Somehow need to scale map to screensize, so that for any map, the screensize if still 1080 x 720

void	render_image(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;
	int	line_length;
	int	end_x;
	int	end_y;

	if (color == SCREEN)
	{
		width = game->width;
		height = game->height;
	}
	else if (color == PLAYER_)
	{
		line_length = SCALE;
		end_x = (start_x + PCENTER) + (line_length * cos(game->player->p_angle));
		end_y = (start_y + PCENTER) + (line_length * sin(game->player->p_angle));
		// draw_line(game, (start_x + PCENTER), (start_y + PCENTER), end_x, end_y, color);
		width = PSIZE;
		height = PSIZE;
	}
	else
	{
		width = SCALE;
		height = SCALE;
	}
	for (int y = start_y; y < start_y + height; y++)
	{
		for (int x = start_x; x < start_x + width; x++)
		{
			if (x == start_x || x == start_x + width - 1 || y == start_y || y == start_y + height - 1)
				put_pixel_to_img(game, x, y, BLACK);
			else
				put_pixel_to_img(game, x, y, color);
		}
	}
}

void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < game->width && y >= 0 && y < game->height)
	{
		int offset = (y * game->img.line_len) + (x * (game->img.bits_per_pixel / 8));
		*(unsigned int *)(game->img.pixels_ptr + offset) = color;
	}
}

void	draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color)
{
	// Mr.Benian's algorithm
	int dx = abs(end_x - start_x);
	int dy = abs(end_y - start_y);
	int sx = (start_x < end_x) ? 1 : -1;
	int sy = (start_y < end_y) ? 1 : -1;
	int err = dx - dy;

	while (true)
	{
		put_pixel_to_img(game, start_x, start_y, color);
		if (start_x == end_x && start_y == end_y)
			break ;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start_x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start_y += sy;
		}
	}
}

void	draw_point(t_game *game, int x, int y, int color)
{
	int	size;

	size = 6;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			put_pixel_to_img(game, x + i, y + j, color);
	}
}
