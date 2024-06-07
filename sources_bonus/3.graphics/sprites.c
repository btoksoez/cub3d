#include "../../includes_bonus/cub3d.h"

t_point	get_normalized_vector(t_point p1, t_point p2)
{
	t_point	dir;
	float	len;

	len = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) *(p2.y - p1.y));
	dir.x = (p2.x - p1.x) / len;
	dir.y = (p2.y - p1.y) / len;
	return (dir);
}

// void	init_enemy_ray(t_raycaster *ray, t_player *player, t_enemy *enemy)
// {
// 	ray->dir = get_normalized_vector(player->pos, enemy->pos);
// 	if (fabs(ray->dir.x) > EPSILON)
// 		ray->scalingf.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
// 	else
// 		ray->scalingf.x = 0;
// 	if (fabs(ray->dir.y) > EPSILON)
// 		ray->scalingf.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
// 	else
// 		ray->scalingf.y = 0;
// 	ray->map_loc.x = (int)player->pos.x / SCALE;
// 	ray->map_loc.y = (int)player->pos.y / SCALE;
// 	ray->start.x = player->pos.x + PCENTER;
// 	ray->start.y = player->pos.y + PCENTER;
// 	if (ray->dir.y < NORTH_)
// 	{
// 		ray->map_step.y = -1;
// 		ray->ray_len.y = (ray->start.y - ray->map_loc.y * SCALE) * ray->scalingf.y;
// 	}
// 	else
// 	{
// 		ray->map_step.y = 1;
// 		ray->ray_len.y = ((ray->map_loc.y + 1) * SCALE - ray->start.y) * ray->scalingf.y;
// 	}
// 	if (ray->dir.x < WEST_)
// 	{
// 		ray->map_step.x = -1;
// 		ray->ray_len.x = (ray->start.x - ray->map_loc.x * SCALE) * ray->scalingf.x;
// 	}
// 	else
// 	{
// 		ray->map_step.x = 1;
// 		ray->ray_len.x = ((ray->map_loc.x + 1) * SCALE - ray->start.x) * ray->scalingf.x;
// 	}
// 	ray->wall = false;
// 	ray->enemy = false;
// 	ray->len = 0;
// }

// void	get_enemy_position(t_game *game, t_raycaster *ray, t_enemy *enemy)
// {
// 	printf("%f %f\n", ray->dir.x, ray->dir.y);
// 	if (game->dir == N_)	//Northwest
// 		ray->len += ((ray->map_loc.y + 1) * SCALE - enemy->pos.y) * ray->scalingf.y;
// 	else if (game->dir == S_) //North east
// 		ray->len += (enemy->pos.y - ray->map_loc.y * SCALE) * ray->scalingf.y;
// 	else if (game->dir == W_) //Southwest
// 		ray->len += ((ray->map_loc.x + 1) * SCALE - enemy->pos.x) * ray->scalingf.x;
// 	else
// 		ray->len += (enemy->pos.x - ray->map_loc.x * SCALE) * ray->scalingf.x;
// }

// float	cast_enemy_ray(t_raycaster *ray, t_enemy *enemy, t_game *game)
// {
// 	int visited;

// 	while (!ray->wall && !ray->enemy)
// 	{
// 		if (ray->ray_len.x < ray->ray_len.y)
// 		{
// 			visited = 1;
// 			ray->len = ray->ray_len.x;
// 			ray->ray_len.x += ray->scalingf.x * SCALE;
// 			ray->map_loc.x += ray->map_step.x;
// 		}
// 		else
// 		{
// 			visited = 2;
// 			ray->len = ray->ray_len.y;
// 			ray->ray_len.y += ray->scalingf.y * SCALE;
// 			ray->map_loc.y += ray->map_step.y;
// 		}
// 		if (game->map->map[ray->map_loc.y][ray->map_loc.x] == WALL)
// 			ray->wall = true;
// 		else if (ray->map_loc.x == (int)(enemy->pos.x / SCALE) && ray->map_loc.y == (int)(enemy->pos.y / SCALE))
// 		{
// 			if (visited == 2)
// 			{
// 				if (ray->dir.y < NORTH_)
// 					game->dir = N_;
// 				else
// 					game->dir = S_;
// 			}
// 			else
// 			{
// 				if (ray->dir.x < WEST_)
// 					game->dir = W_;
// 				else
// 					game->dir = E_;
// 			}
// 			ray->enemy = true;
// 			get_enemy_position(game, ray, enemy);
// 		}
// 	}
// 	// printf("%d, %d; %f, %f\n", ray->map_loc.x, ray->map_loc.y, enemy->pos.x / SCALE, enemy->pos.y / SCALE);
// 	// printf("%f, %f; %f, %f\n", ray->start.x + ray->dir.x * ray->len, ray->start.y + ray->dir.y * ray->len, enemy->pos.x, enemy->pos.y);
// 	draw_line(game, ray->start.x, ray->start.y, ray->start.x + ray->dir.x * ray->len, ray->start.y + ray->dir.y * ray->len, BLUE);
// 	return (ray->len);
// }

bool	enemy_in_tile(int x, int y, t_game *game)
{
	t_enemy	**enemy;
	int		i;

	i = 0;
	enemy = game->enemies;
	while (i < game->enemy_count)
	{
		if (x == (int)(enemy[i]->pos.x / SCALE) && y == (int)(enemy[i]->pos.y / SCALE))
			return (true);
		i++;
	}
	return (false);

}

bool	lines_intersect(t_point p1, t_point p2, t_enemy *enemy, t_point *intersection)
{
	float	denominator;
	t_point	p3;
	t_point	p4;
	float	t;
	float	u;

	p3 = enemy->left;
	p4 = enemy->right;

	denominator = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	if (denominator == 0)	//lines are parallel
		return (false);
	t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / denominator;
	u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / denominator;

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
	{
		intersection->x = p1.x + t * (p2.x - p1.x);
		intersection->y = p1.y + t * (p2.y - p1.y);
		return (true);
	}
	return (false);
}

//is called if an enemy is in a tile
//check whether the ray hits an enemy line
void	get_enemy_distance(t_raycaster *ray, t_game *game)
{
	t_point	ray_end;
	t_enemy	**enemy;
	t_point	intersection;
	int		i;
	float	distance;

	ray_end.x = ray->start.x + ray->dir.x * ray->len;
	ray_end.y = ray->start.y + ray->dir.y * ray->len;
	enemy = game->enemies;
	i = 0;
	while (i < game->enemy_count)
	{
		if (lines_intersect(ray->start, ray_end, enemy[i], &intersection))
		{
			ray->enemy = enemy[i]->type;
			distance = sqrt(pow(ray->start.x - intersection.x, 2) + pow(ray->start.y - intersection.y, 2));
			if (distance <= ray->distance_enemy)
			{
				ray->distance_enemy = distance;
				ray->enemy_fraction_x = fmod(intersection.x, (float)PSIZE) / (float)PSIZE;
				ray->enemy_fraction_y = fmod(intersection.y, (float)PSIZE) / (float)PSIZE;
				draw_line(game, ray->start.x, ray->start.y, intersection.x, intersection.y, ray->enemy);
			}
		}
		i++;
	}
}

int	get_enemy_color(t_game *game, int enemy_type, int tex_x, int tex_y)
{
	int			color;
	int			bpp;
	int			len;
	t_textures	*t;

	color = 0;
	t = game->textures;
	bpp = t->enemy[enemy_type].bits_per_pixel;
	len = t->enemy[enemy_type].line_len;
	color = *(int*)&t->enemy[enemy_type].pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	return (color);
}

void	draw_enemy(t_game *game, int start_x, t_raycaster *ray)
{
	int		color;

	float	tex_y;
	float	tex_x;
	float	step;
	t_point	top;
	t_point	bottom;
	int		enemy_height;

	enemy_height = (ENEMY_SCALE / ray->distance_enemy);
	top.y = (HEIGHT / 2) - enemy_height + game->player->jump_height;
	bottom.y = (HEIGHT / 2) + enemy_height + game->player->jump_height;

	tex_y = 0;
	tex_x = game->textures->enemy[ray->enemy].width * (ray->enemy_fraction_x + ray->enemy_fraction_y);
	step = (float)game->textures->north.height / (bottom.y - top.y);
	while (top.y <= bottom.y)
	{
		color = get_enemy_color(game, ray->enemy, tex_x, tex_y);
		put_pixel_to_img(game, start_x, top.y, color);
		top.y++;
		tex_y += step;
	}
}



// 	int			i;
// 	t_player	*player;
// 	t_raycaster ray[game->enemy_count];
// 	t_enemy		**enemy;
// 	float		distance;
// 	// float		adjusted;
// 	t_point		top;
// 	t_point		bottom;
// 	int			wall_height;

// 	i = 0;
// 	player = game->player;
// 	enemy = game->enemies;
// 	while (i < game->enemy_count)
// 	{
// 		init_enemy_ray(&ray[i], player, enemy[i]);
// 		distance = cast_enemy_ray(&ray[i], enemy[i], game);
// 		// adjusted = distance * cos(angle - player->p_angle);
// 		wall_height = (WALL_SCALE / distance);
// 		top.y = (HEIGHT / 2) - wall_height + player->jump_height;
// 		bottom.y = (HEIGHT / 2) + wall_height + player->jump_height;
// 		draw_vline(game, WIDTH /2, bottom.y, WIDTH / 2, bottom.y, BLACK);
// 		i++;
// 		//sprite movement:
// 			//move always in direction of player until can't go forward, then decrease x and y towards player x and y
// 	}
// }
