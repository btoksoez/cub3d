#include "../../includes/cub3d.h"

void	init_raycaster(t_raycaster *ray, t_player *player)
{
	ray->dir.x = cos(player->p_angle);
	ray->dir.y = sin(player->p_angle);
	ray->stepsize.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
	ray->stepsize.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
	ray->tile_map.x = (int)player->pos.x;
	ray->tile_map.y = (int)player->pos.y;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->ray_len.x = (player->pos.x - (float)ray->tile_map.x) * ray->stepsize.x;	//to calculate first step
	}
	else
	{
		ray->step.x = 1;
		ray->ray_len.x = ((float)(ray->tile_map.x + 1) - player->pos.x) * ray->stepsize.x;	//to calculate first step
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->ray_len.y = (player->pos.y - (float)ray->tile_map.y) * ray->stepsize.y;	//to calculate first step
	}
	else
	{
		ray->step.y = 1;
		ray->ray_len.y = ((float)(ray->tile_map.y + 1) - player->pos.y) * ray->stepsize.y;	//to calculate first step
	}
	ray->len = 0;
	ray->wall = false;
}

void	cast_rays(t_game *game)
{
	t_player	*player;
	t_raycaster	ray;

	player = game->player;
	init_raycaster(&ray, player);
	while (!ray.wall)
	{
		if (ray.ray_len.x < ray.ray_len.y)
		{
			ray.tile_map.x += ray.step.x;
			ray.len = ray.ray_len.x;
			ray.ray_len.x += ray.stepsize.x;
		}
		else
		{
			ray.tile_map.y += ray.step.y;
			ray.len = ray.ray_len.y;
			ray.ray_len.y += ray.stepsize.y;
		}
		printf("ray tile map y: %d, tile map x: %d\n", ray.tile_map.y, ray.tile_map.x);
		if (game->map->map[ray.tile_map.y / SCALE][ray.tile_map.x / SCALE] == WALL)
			ray.wall = true;
	}
	if (ray.wall)
	{
		ray.intersection.x = player->pos.x + ray.dir.x * ray.len;
		ray.intersection.y = player->pos.y + ray.dir.y * ray.len;
		draw_line(game, player->pos.x + PCENTER, player->pos.y + PCENTER, ray.intersection.x, ray.intersection.y, MAGENTA);
	}
}
