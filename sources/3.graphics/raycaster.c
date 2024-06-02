#include "../../includes/cub3d.h"

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

float	cast_ray(t_game *game, float angle)
{
	t_raycaster	ray;
	t_player	*player;
	int			visited;

	visited = 0;
	player = game->player;
	init_ray(&ray, player, angle);
	while (!ray.wall)
	{
		if (ray.ray_len.x < ray.ray_len.y)
		{
			visited = 1;
			ray.len = ray.ray_len.x;
			ray.ray_len.x += ray.scalingf.x * SCALE;
			ray.map_loc.x += ray.map_step.x;
		}
		else
		{
			visited = 2;
			ray.len = ray.ray_len.y;
			ray.ray_len.y += ray.scalingf.y * SCALE;
			ray.map_loc.y += ray.map_step.y;
		}
		if (game->map->map[ray.map_loc.y][ray.map_loc.x] == WALL)
		{
			if (visited == 2 && angle > PI && angle < PI_2)
				game->dir = N_;
			else if (visited == 2 && angle < PI && angle > 0)
				game->dir = S_;
			else if (visited == 1 && angle < PI_15 && angle > PI_05)
				game->dir = W_;
			else if (visited == 1 && angle > PI_15 && angle < PI_05)
				game->dir = E_;
			printf("%d\n", game->dir);
			ray.wall = true;
		}
	}
	draw_line(game, ray.start.x, ray.start.y, ray.start.x + ray.dir.x * ray.len, ray.start.y + ray.dir.y * ray.len, BLUE);
	return (ray.len);
}

void	cast_rays(t_game *game)
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
		distance = cast_ray(game, angle);
		adjusted = distance * cos(angle - player->p_angle);
		wall_height = (WALL_SCALE / adjusted);
		top.y = (HEIGHT / 2) - wall_height;
		bottom.y = (HEIGHT / 2) + wall_height;
		draw_vline(game, x, top.y, x, bottom.y, game->dir);
		draw_vline(game, x, bottom.y, x, HEIGHT, game->f_color);
		draw_vline(game, x, 0, x, top.y, game->c_color);
		angle += (PLAYER_VISION / WIDTH);
		x++;
	}
}
