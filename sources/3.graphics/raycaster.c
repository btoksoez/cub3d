// #include "../../includes/cub3d.h"

// void	init_raycaster(t_raycaster *ray, t_player *player)
// {
// 	ray->dir.x = cos(player->p_angle);
// 	ray->dir.y = sin(player->p_angle);
// 	ray->scalingf.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
// 	ray->scalingf.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
// 	ray->map_loc.x = (int)player->pos.x;
// 	ray->map_loc.y = (int)player->pos.y;
// 	if (ray->dir.x < 0)
// 	{
// 		ray->map_step.x = -1;
// 		ray->ray_len.x = (player->pos.x - (float)ray->map_loc.x) * ray->scalingf.x;	//to calculate first map_step
// 	}
// 	else
// 	{
// 		ray->map_step.x = 1;
// 		ray->ray_len.x = ((float)(ray->map_loc.x + 1) - player->pos.x) * ray->scalingf.x;	//to calculate first map_step
// 	}
// 	if (ray->dir.y < 0)
// 	{
// 		ray->map_step.y = -1;
// 		ray->ray_len.y = (player->pos.y - (float)ray->map_loc.y) * ray->scalingf.y;	//to calculate first map_step
// 	}
// 	else
// 	{
// 		ray->map_step.y = 1;
// 		ray->ray_len.y = ((float)(ray->map_loc.y + 1) - player->pos.y) * ray->scalingf.y;	//to calculate first map_step
// 	}
// 	ray->len = 0;
// 	ray->wall = false;
// }

// void	cast_rays(t_game *game)
// {
// 	t_player	*player;
// 	t_raycaster	ray;

// 	player = game->player;
// 	init_raycaster(&ray, player);
// 	while (!ray.wall)
// 	{
// 		if (ray.ray_len.x < ray.ray_len.y)
// 		{
// 			ray.map_loc.x += ray.map_step.x;
// 			ray.len = ray.ray_len.x;
// 			ray.ray_len.x += ray.scalingf.x;
// 		}
// 		else
// 		{
// 			ray.map_loc.y += ray.map_step.y;
// 			ray.len = ray.ray_len.y;
// 			ray.ray_len.y += ray.scalingf.y;
// 		}
// 		printf("ray tile map y: %d, tile map x: %d\n", ray.map_loc.y, ray.map_loc.x);
// 		if (game->map->map[ray.map_loc.y / SCALE][ray.map_loc.x / SCALE] == WALL)
// 			ray.wall = true;
// 	}
// 	if (ray.wall)
// 	{
// 		ray.intersection.x = player->pos.x + ray.dir.x * ray.len;
// 		ray.intersection.y = player->pos.y + ray.dir.y * ray.len;
// 		draw_line(game, player->pos.x + PCENTER, player->pos.y + PCENTER, ray.intersection.x, ray.intersection.y, MAGENTA);
// 	}
// }
