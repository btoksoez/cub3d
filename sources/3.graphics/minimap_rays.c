#include "../../includes/cub3d.h"

void	raycast_2d(t_game *game, t_raycaster *ray, t_minimap mini)
{
	t_player	*player;
	float		angle;

	player = game->player;
	angle = player->p_angle - (PLAYER_VISION / 2);
	while (angle < player->p_angle + (PLAYER_VISION / 2))
	{
		cast_2d_ray(game, angle, ray, mini);
		angle += (PLAYER_VISION / WIDTH);
	}
}

void	cast_2d_ray(t_game *game, float angle, t_raycaster *ray, t_minimap mini)
{
	t_player	*player;
	int			visited;

	visited = 0;
	player = game->player;
	init_2d_ray(ray, player, angle);
	while (!ray->wall)
	{
		if (ray->ray_len.x < ray->ray_len.y)
		{
			visited = 1;
			ray->len = ray->ray_len.x;
			ray->ray_len.x += ray->scalingf.x * MINI_SCALE;
			ray->map_loc.x += ray->map_step.x;
		}
		else
		{
			visited = 2;
			ray->len = ray->ray_len.y;
			ray->ray_len.y += ray->scalingf.y * MINI_SCALE;
			ray->map_loc.y += ray->map_step.y;
		}
		if (game->map->map[ray->map_loc.y][ray->map_loc.x] == WALL)
			check_direction(game, ray, visited);
	}
	adjust_raylen(ray, angle);
	draw_ray(game, player, ray, mini);
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
		ray->ray_len.y = (ray->start.y - ray->map_loc.y * MINI_SCALE) * ray->scalingf.y;
	}
	else
	{
		ray->map_step.y = 1;
		ray->ray_len.y = ((ray->map_loc.y + 1) * MINI_SCALE - ray->start.y) * ray->scalingf.y;
	}
	if (ray->dir.x < WEST_)
	{
		ray->map_step.x = -1;
		ray->ray_len.x = (ray->start.x - ray->map_loc.x * MINI_SCALE) * ray->scalingf.x;
	}
	else
	{
		ray->map_step.x = 1;
		ray->ray_len.x = ((ray->map_loc.x + 1) * MINI_SCALE - ray->start.x) * ray->scalingf.x;
	}
	ray->wall = false;
	ray->len = 0;
}

void	adjust_raylen(t_raycaster *ray, float angle)
{
	float		max_dist_x;
	float		max_dist_y;
	float		true_max_x;
	float		true_max_y;

	max_dist_y = MINI_ROWS * MINI_SCALE / 2;
	max_dist_x = MINI_COLS * MINI_SCALE / 2;
	true_max_y = fabs(max_dist_y / cos(_15PI - angle));
	true_max_x = fabs(max_dist_x / cos(angle - PI));
	if (true_max_x > true_max_y && ray->len > true_max_y)
		ray->len = true_max_y;
	else if (true_max_x < true_max_y && ray->len > true_max_x)
		ray->len = true_max_x;
}

void	draw_ray(t_game *game, t_player *player, t_raycaster *ray, t_minimap mini)
{
	// need fix on here1 and 2 when for the ray len
	if ((player->pos.x <= mini.hori_vision) && (player->pos.y <= mini.vert_vision)) // NEEDS FIX
	{
		draw_line(game, CLOSE_TO_BOUND_POSITION_X, CLOSE_TO_BOUND_POSITION_Y,
		CLOSE_TO_BOUND_POSITION_X + (ray->dir.x * ray->len),
		CLOSE_TO_BOUND_POSITION_Y + (ray->dir.y * ray->len), BLUE);
	}
	else if (player->pos.y <= mini.vert_vision) // NEEDS FIX
	{
		draw_line(game, CENTERED_POSITION_X, CLOSE_TO_BOUND_POSITION_Y,
		CENTERED_POSITION_X + (ray->dir.x * ray->len),
		CLOSE_TO_BOUND_POSITION_Y + (ray->dir.y * ray->len), BLUE);
	}
	else if (player->pos.x <= mini.hori_vision)
	{
		draw_line(game, CLOSE_TO_BOUND_POSITION_X, CENTERED_POSITION_Y,
		CLOSE_TO_BOUND_POSITION_X + (ray->dir.x * ray->len),
		CENTERED_POSITION_Y + (ray->dir.y * ray->len), BLUE);
	}
	else
	{
		draw_line(game, CENTERED_POSITION_X, CENTERED_POSITION_Y,
		CENTERED_POSITION_X + (ray->dir.x * ray->len),
		CENTERED_POSITION_Y + (ray->dir.y * ray->len), BLUE);
	}
}
