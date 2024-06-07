#include "../../includes/cub3d.h"

void	raycast(t_game *game, t_raycaster *ray)
{
	t_player	*player;
	float		distance;
	float		adjusted;
	t_point		top;
	t_point		bottom;
	int			x;
	float		angle;
	int			wall_height;

	player = game->player;
	angle = player->p_angle - (PLAYER_VISION / 2);
	x = 0;
	while (angle < player->p_angle + (PLAYER_VISION / 2))
	{
		distance = cast_ray(game, angle, ray);
		adjusted = distance * cos(angle - player->p_angle);
		wall_height = (WALL_SCALE / adjusted);
		top.y = (HEIGHT / 2) - wall_height + player->jump_height;
		bottom.y = (HEIGHT / 2) + wall_height + player->jump_height;
		draw_textures(game, x, top.y, x, bottom.y);
		draw_vline(game, x, bottom.y, x, HEIGHT, game->f_color);
		draw_vline(game, x, 0, x, top.y, game->c_color);
		angle += (PLAYER_VISION / WIDTH);
		x++;
	}
}

void	cast_2d_rays(t_game *game, t_raycaster *ray, int hori_vision, int vert_vision)
{
	t_player	*player;
	float		angle;

	player = game->player;
	angle = player->p_angle - (PLAYER_VISION / 2);
	while (angle < player->p_angle + (PLAYER_VISION / 2))
	{
		cast_2d_ray(game, angle, ray, hori_vision, vert_vision);
		angle += (PLAYER_VISION / WIDTH);
	}
}

void	init_2d_ray(t_raycaster *ray, t_player *player, float angle)
{
	ray->dir.x = cos(angle);
	ray->dir.y = sin(angle);
	ray->scalingf.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
	ray->scalingf.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
	ray->map_loc.x = (int)player->pos.x / SCALE;
	ray->map_loc.y = (int)player->pos.y / SCALE;
	ray->start.x = (player->pos.x + PCENTER) / 2;
	ray->start.y = (player->pos.y + PCENTER) / 2;
	if (ray->dir.y < NORTH_)
	{
		ray->map_step.y = -1;
		ray->ray_len.y = (ray->start.y - ray->map_loc.y * (SCALE / 2)) * ray->scalingf.y;
	}
	else
	{
		ray->map_step.y = 1;
		ray->ray_len.y = ((ray->map_loc.y + 1) * (SCALE / 2) - ray->start.y) * ray->scalingf.y;
	}
	if (ray->dir.x < WEST_)
	{
		ray->map_step.x = -1;
		ray->ray_len.x = (ray->start.x - ray->map_loc.x * (SCALE / 2)) * ray->scalingf.x;
	}
	else
	{
		ray->map_step.x = 1;
		ray->ray_len.x = ((ray->map_loc.x + 1) * (SCALE / 2) - ray->start.x) * ray->scalingf.x;
	}
	ray->wall = false;
	ray->len = 0;
}

void	cast_2d_ray(t_game *game, float angle, t_raycaster *ray, int hori_vision, int vert_vision)
{
	t_player	*player;
	int			visited;
	float		max_dist_x;
	float		true_max_x;
	float		max_dist_y;
	float		true_max_y;

	visited = 0;
	player = game->player;
	init_2d_ray(ray, player, angle);
	max_dist_y = 5 * (SCALE / 2) / 2;
	max_dist_x = 7 * (SCALE / 2) / 2;
	true_max_y = fabs(max_dist_y / cos(_15PI - angle));
	true_max_x = fabs(max_dist_x / cos(angle - PI));
	while (!ray->wall)
	{
		if (ray->ray_len.x < ray->ray_len.y)
		{
			visited = 1;
			ray->len = ray->ray_len.x;
			ray->ray_len.x += ray->scalingf.x * (SCALE / 2);
			ray->map_loc.x += ray->map_step.x;
		}
		else
		{
			visited = 2;
			ray->len = ray->ray_len.y;
			ray->ray_len.y += ray->scalingf.y * (SCALE / 2);
			ray->map_loc.y += ray->map_step.y;
		}
		if (game->map->map[ray->map_loc.y][ray->map_loc.x] == WALL)
		{
			if (visited == 2)
			{
				if (ray->dir.y < NORTH_)
					game->dir = N_;
				else
					game->dir = S_;
			}
			else
			{
				if (ray->dir.x < WEST_)
					game->dir = W_;
				else
					game->dir = E_;
			}
			ray->wall = true;
		}
	}
	if (true_max_x > true_max_y && ray->len > true_max_y)
		ray->len = true_max_y;
	else if (true_max_x < true_max_y && ray->len > true_max_x)
		ray->len = true_max_x;

	if ((player->pos.x <= hori_vision) && (player->pos.y <= vert_vision)) // NEEDS FIX
	{
		printf("here1\n");
		draw_line(game, CLOSE_TO_BOUND_POSITION_X, CLOSE_TO_BOUND_POSITION_Y,
		CLOSE_TO_BOUND_POSITION_X + (ray->dir.x * ray->len),
		CLOSE_TO_BOUND_POSITION_Y + (ray->dir.y * ray->len), BLUE);
	}
	else if (player->pos.y <= vert_vision) // NEEDS FIX
	{
		printf("here2\n");
		draw_line(game, CENTERED_POSITION_X, CLOSE_TO_BOUND_POSITION_Y,
		CENTERED_POSITION_X + (ray->dir.x * ray->len),
		CLOSE_TO_BOUND_POSITION_Y + (ray->dir.y * ray->len), BLUE);
	}
	else if (player->pos.x <= hori_vision)
	{
		printf("here3\n");
		draw_line(game, CLOSE_TO_BOUND_POSITION_X, CENTERED_POSITION_Y,
		CLOSE_TO_BOUND_POSITION_X + (ray->dir.x * ray->len),
		CENTERED_POSITION_Y + (ray->dir.y * ray->len), BLUE);
	}
	else
	{
		printf("here4\n");
		draw_line(game, CENTERED_POSITION_X, CENTERED_POSITION_Y,
		CENTERED_POSITION_X + (ray->dir.x * ray->len),
		CENTERED_POSITION_Y + (ray->dir.y * ray->len), BLUE);
	}
}

float	cast_ray(t_game *game, float angle, t_raycaster *ray)
{
	t_player	*player;
	int			visited;

	visited = 0;
	player = game->player;
	init_ray(ray, player, angle);
	while (!ray->wall)
	{
		if (ray->ray_len.x < ray->ray_len.y)
		{
			visited = 1;
			ray->len = ray->ray_len.x;
			ray->ray_len.x += ray->scalingf.x * SCALE;
			ray->map_loc.x += ray->map_step.x;
		}
		else
		{
			visited = 2;
			ray->len = ray->ray_len.y;
			ray->ray_len.y += ray->scalingf.y * SCALE;
			ray->map_loc.y += ray->map_step.y;
		}
		if (game->map->map[ray->map_loc.y][ray->map_loc.x] == WALL)
		{
			if (visited == 2)
			{
				if (ray->dir.y < NORTH_)
					game->dir = N_;
				else
					game->dir = S_;
			}
			else
			{
				if (ray->dir.x < WEST_)
					game->dir = W_;
				else
					game->dir = E_;
			}
			ray->wall = true;
		}
	}
	game->fraction_x = fmod((ray->start.x + ray->dir.x * ray->len), (float)SCALE) / (float)SCALE;
	game->fraction_y = fmod((ray->start.y + ray->dir.y * ray->len), (float)SCALE) / (float)SCALE;
	return (ray->len);
}

void	init_ray(t_raycaster *ray, t_player *player, float angle)
{
	ray->dir.x = cos(angle);
	ray->dir.y = sin(angle);
	ray->scalingf.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
	ray->scalingf.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
	ray->map_loc.x = (int)player->pos.x / SCALE;
	ray->map_loc.y = (int)player->pos.y / SCALE;
	ray->start.x = player->pos.x + PCENTER;
	ray->start.y = player->pos.y + PCENTER;
	if (ray->dir.y < NORTH_)
	{
		ray->map_step.y = -1;
		ray->ray_len.y = (ray->start.y - ray->map_loc.y * SCALE) * ray->scalingf.y;
	}
	else
	{
		ray->map_step.y = 1;
		ray->ray_len.y = ((ray->map_loc.y + 1) * SCALE - ray->start.y) * ray->scalingf.y;
	}
	if (ray->dir.x < WEST_)
	{
		ray->map_step.x = -1;
		ray->ray_len.x = (ray->start.x - ray->map_loc.x * SCALE) * ray->scalingf.x;
	}
	else
	{
		ray->map_step.x = 1;
		ray->ray_len.x = ((ray->map_loc.x + 1) * SCALE - ray->start.x) * ray->scalingf.x;
	}
	ray->wall = false;
	ray->len = 0;
}
