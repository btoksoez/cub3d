#include "../../includes/cub3d.h"

void	init_ray(t_raycaster *ray, t_player *player, float angle, t_game *game)
{
	ray->dir.x = cos(angle);
	ray->dir.y = sin(angle);
	ray->scalingf.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
	ray->scalingf.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
	ray->map_loc.x = (int)player->pos.x / game->xscale;
	ray->map_loc.y = (int)player->pos.y / game->yscale;
	ray->start.x = player->pos.x + PCENTER;
	ray->start.y = player->pos.y + PCENTER;
	if (ray->dir.y < NORTH)
	{
		ray->map_step.y = -1;
		ray->ray_len.y = (ray->start.y - ray->map_loc.y * game->yscale) * ray->scalingf.y;
	}
	else
	{
		ray->map_step.y = 1;
		ray->ray_len.y = ((ray->map_loc.y + 1) * game->yscale - ray->start.y) * ray->scalingf.y;
	}
	if (ray->dir.x < WEST)
	{
		ray->map_step.x = -1;
		ray->ray_len.x = (ray->start.x - ray->map_loc.x * game->xscale) * ray->scalingf.x;
	}
	else
	{
		ray->map_step.x = 1;
		ray->ray_len.x = ((ray->map_loc.x + 1) * game->xscale - ray->start.x) * ray->scalingf.x;
	}
	ray->wall = false;
	ray->len = 0;
}

float	cast_ray(t_game *game, float angle)
{
	t_raycaster	ray;
	t_player	*player;

	player = game->player;
	init_ray(&ray, player, angle, game);
	while (!ray.wall)
	{
		if (ray.ray_len.x < ray.ray_len.y)
		{
			ray.len = ray.ray_len.x;
			ray.ray_len.x += ray.scalingf.x * game->xscale;
			ray.map_loc.x += ray.map_step.x;
		}
		else
		{
			ray.len = ray.ray_len.y;
			ray.ray_len.y += ray.scalingf.y * game->yscale;
			ray.map_loc.y += ray.map_step.y;
		}
		if (game->map->map[ray.map_loc.y][ray.map_loc.x] == WALL)
			ray.wall = true;
	}
	// draw_line(game, ray.start.x, ray.start.y, ray.start.x + ray.dir.x * ray.len, ray.start.y + ray.dir.y * ray.len, BLUE);
	return (ray.len);
}

void	cast_rays(t_game *game)
{
	t_player	*player;
	float		distance;
	t_point		top;
	float		angle;

	player = game->player;
	angle = player->p_angle - (PLAYER_VISION / 2);
	while (angle < player->p_angle + (PLAYER_VISION / 2))
	{
		distance = cast_ray(game, angle);
		top.y = WIDTH / 2 + distance / tan(PI / 6);
		draw_line(game, WIDTH / 2, HEIGHT / 2, WIDTH / 2, top.y, BLUE);
		angle += (PLAYER_VISION / RAY_DENSITY);
	}
}
