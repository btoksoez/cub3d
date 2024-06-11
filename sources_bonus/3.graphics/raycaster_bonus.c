#include "../../includes_bonus/cub3d.h"

int	get_fc_color(t_game *game, int tex_x, int tex_y, bool floor_ceiling)
{
	int			color;
	int			bpp;
	int			len;
	t_textures	*t;

	color = 0;
	t = game->textures;
	if (!floor_ceiling)
	{
		bpp = t->ground.bits_per_pixel;
		len = t->ground.line_len;
		color = *(int*)&t->ground.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	}
	else
	{
		bpp = t->sky.bits_per_pixel;
		len = t->sky.line_len;
		color = *(int*)&t->sky.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	}
	return (color);
}

void	draw_ceiling(t_game *game, int x, int bottom, int top)
{
	int		temp;
	int		color;
	float	tex_y;
	float	tex_x;
	float	step;

	temp = 0;
	if (bottom > top)
	{
		temp = bottom;
		bottom = top;
		top = temp;
	}
	tex_y = 0;
	tex_x = game->textures->sky.width * (game->fraction_x + game->fraction_y);
	step = (float)game->textures->sky.height / (top - bottom);
	while (bottom <= top)
	{
		color = get_fc_color(game, tex_x, tex_y, true);
		put_pixel_to_img(game, x, bottom, color);
		bottom++;
		tex_y += step;
	}
}

void	draw_floor(t_game *game, int x, int bottom, int top)
{
	int		temp;
	int		color;
	float	tex_y;
	float	tex_x;
	float	step;

	temp = 0;
	if (bottom > top)
	{
		temp = bottom;
		bottom = top;
		top = temp;
	}
	tex_y = 0;
	tex_x = game->textures->ground.width * (game->fraction_x + game->fraction_y);
	step = (float)game->textures->ground.height / (top - bottom);
	while (bottom <= top)
	{
		color = get_fc_color(game, tex_x, tex_y, false);
		put_pixel_to_img(game, x, bottom, color);
		bottom++;
		tex_y += step;
	}
}

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
	game->hit_enemy = -1;
	x = 0;
	while (angle < player->p_angle + (PLAYER_VISION / 2))
	{
		distance = cast_ray(ray, game, angle);
		adjusted = distance * cos(angle - player->p_angle);
		wall_height = (WALL_SCALE / adjusted);
		top.y = (HEIGHT / 2) - wall_height + player->jump_height;
		bottom.y = (HEIGHT / 2) + wall_height + player->jump_height;
		draw_textures(game, x, top.y, x, bottom.y);
		draw_floor(game, x, bottom.y, HEIGHT);
		draw_ceiling(game, x, 0, top.y);
		get_enemy_distance(ray, game);
		if (ray->enemy)
		{
			// printf("here\n");
			game->hit_enemy = ray->enemy_id;
			ray->distance_enemy *= cos(angle - player->p_angle);
			draw_enemy(game, x, ray);
		}
		angle += (PLAYER_VISION / WIDTH);
		x++;
	}
}

float	cast_ray(t_raycaster *ray, t_game *game, float angle)
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
	ray->map_loc.x = (int)(player->pos.x + PCENTER) / SCALE;
	ray->map_loc.y = (int)(player->pos.y + PCENTER) / SCALE;
	ray->start.x = player->pos.x + PCENTER;
	ray->start.y = player->pos.y + PCENTER;
	ray->wall = false;
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
	ray->len = 0;
	ray->enemy = false;
	ray->enemy_type = -1;
	ray->distance_enemy = (float)INT_MAX;
	ray->tex_x = 0;
	ray->enemy_id = 0;
}

void	check_direction(t_game *game, t_raycaster *ray, int visited)
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
