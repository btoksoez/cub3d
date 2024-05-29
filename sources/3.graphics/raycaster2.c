#include "../../includes/cub3d.h"

void	init_raycaster(t_raycaster *ray, t_player *player)
{
	ray->dir.x = cos(player->p_angle);
	ray->dir.y = sin(player->p_angle);
	ray->scalingf.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
	ray->scalingf.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
	ray->map_loc.x = (int)player->pos.x;
	ray->map_loc.y = (int)player->pos.y;

	printf("maplocx: %d, maplocy: %d\n", ray->map_loc.x, ray->map_loc.y);
	if (ray->dir.y < NORTH)
	{
		ray->map_step.y = -1;
		ray->ray_len.y = (player->pos.y - ray->map_loc.y) * ray->scalingf.y;
	}
	else
	{
		ray->map_step.y = 1;
		ray->ray_len.y = (ray->map_loc.y + 1 - player->pos.y) * ray->scalingf.y;
	}
	if (ray->dir.x < WEST)
	{
		ray->map_step.x = -1;
		ray->ray_len.x = (player->pos.x - ray->map_loc.x) * ray->scalingf.x;
	}
	else
	{
		ray->map_step.x = 1;
		ray->ray_len.x = (ray->map_loc.x + 1 - player->pos.x) * ray->scalingf.x;
	}
	ray->wall = false;
	ray->len = 0;
}

int round_to_nearest_50(int num) {
    return round(num / 50.0) * 50;
}

void	cast_rays(t_game *game)
{
	t_raycaster	ray;
	t_player	*player;

	player = game->player;
	init_raycaster(&ray, player);
	while (!ray.wall)
	{
		if (ray.ray_len.x < ray.ray_len.y)
		{
			ray.len = ray.ray_len.x;
			ray.ray_len.x += ray.scalingf.x;
			ray.map_loc.x += ray.map_step.x;
		}
		else
		{
			ray.len = ray.ray_len.y;
			ray.ray_len.y += ray.scalingf.y;
			ray.map_loc.y += ray.map_step.y;
		}
		printf("Ray len x: %f Ray Len Y: %f\nmap loc x: %d, map loc y: %d\n", ray.ray_len.x, ray.ray_len.y, ray.map_loc.x, ray.map_loc.y);
		printf("PLayer pos: %f %f\n\n", player->pos.x, player->pos.y);
		if (game->map->map[(ray.map_loc.y) / SCALE][(ray.map_loc.x) / SCALE] == WALL)
			ray.wall = true;
	}
	draw_line(game, player->pos.x + PCENTER, player->pos.y + PCENTER, player->pos.x + ray.dir.x * ray.len, player->pos.y + ray.dir.y * ray.len, MAGENTA);
}
