#include "../../includes/cub3d.h"

void	init_ray(t_raycaster *ray, t_player *player, float angle);
{
	ray->dir.x = cos(angle);
	ray->dir.y = sin(angle);
	ray->scalingf.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
	ray->scalingf.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
	ray->map_loc.x = (int)player->pos.x / SCALE;
	ray->map_loc.y = (int)player->pos.y / SCALE;
	ray->start.x = player->pos.x + PCENTER;
	ray->start.y = player->pos.y + PCENTER;
	if (ray->dir.y < NORTH)
	{
		ray->map_step.y = -1;
		ray->ray_len.y = (ray->start.y - ray->map_loc.y * SCALE) * ray->scalingf.y;
	}
	else
	{
		ray->map_step.y = 1;
		ray->ray_len.y = ((ray->map_loc.y + 1) * SCALE - ray->start.y) * ray->scalingf.y;
	}
	if (ray->dir.x < WEST)
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

void	cast_ray(t_game *game, float angle)
{
	t_raycaster	ray;
	t_player	*player;

	player = game->player;
	init_ray(&ray, player, angle);
	int i = 0;
	while (!ray.wall)
	{
		if (ray.ray_len.x < ray.ray_len.y)
		{
			ray.len = ray.ray_len.x;
			ray.ray_len.x += ray.scalingf.x * SCALE;
			ray.map_loc.x += ray.map_step.x;
		}
		else
		{
			ray.len = ray.ray_len.y;
			ray.ray_len.y += ray.scalingf.y * SCALE;
			ray.map_loc.y += ray.map_step.y;
		}
		// printf("Map loc: %d, %d\nRay Len: %f\nRaylenx %f, Rayleny %f\n", ray.map_loc.x, ray.map_loc.y, ray.len, ray.ray_len.x, ray.ray_len.y);
		i++;
		if (game->map->map[ray.map_loc.y][ray.map_loc.x] == WALL)
			ray.wall = true;
	}
	printf("%d\n", i);
	draw_line(game, ray.start.x, ray.start.y, ray.start.x + ray.dir.x * ray.len, ray.start.y + ray.dir.y * ray.len, MAGENTA);
}

void	cast_rays(t_game *game)
{
	
}

