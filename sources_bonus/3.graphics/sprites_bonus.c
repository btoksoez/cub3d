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

// Function to compute the cross product of two vectors
float	cross_product(t_point a, t_point b)
{
	return ((a.x * b.y) - (a.y * b.x));
}

// Function to check if two line segments (p1, p2) and (q1, q2) intersect
bool	lines_intersect(t_point p1, t_point p2, t_enemy *enemy, t_point *intersection)
{
	t_point	q1;
	t_point	q2;
	t_point	r;
	t_point	s;
	float	cross;
	float	t;
	float	u;

	q1 = enemy->left;
	q2 = enemy->right;
	r.x = p2.x - p1.x;
	r.y = p2.y - p1.y;
	s.x = q2.x - q1.x;
	s.y = q2.y - q1.y;
	cross = cross_product(r, s);
	if (cross == 0)
		return false;
	t_point qp = { q1.x - p1.x, q1.y - p1.y };
	t = cross_product(qp, s) / cross;
	u = cross_product(qp, r) / cross;

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
	{
		// Compute the intersection point
		intersection->x = p1.x + t * r.x;
		intersection->y = p1.y + t * r.y;
		return (true);
	}
	return (false);
}

//is called after ray is casted
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
			distance = hypot(ray->start.x - intersection.x, ray->start.y - intersection.y);
			if (distance < ray->distance_enemy)  // this function is triggerring when it shouldn't
			{
				float enemy_line_length = hypot(enemy[i]->right.x - enemy[i]->left.x, enemy[i]->right.y - enemy[i]->left.y);
				float intersection_pos = hypot(intersection.x - enemy[i]->left.x, intersection.y - enemy[i]->left.y) / enemy_line_length;
				ray->enemy_type = enemy[i]->type;
				ray->enemy_id = i;
				ray->enemy = true;
				ray->distance_enemy = distance;
				ray->tex_x = intersection_pos * game->textures->enemy[ray->enemy_type][0].width;
			}
		}
		i++;
	}
}

int	get_enemy_color(t_game *game, t_raycaster *ray, int tex_x, int tex_y)
{
	int			color;
	int			bpp;
	int			len;
	int			frame;
	t_textures	*t;

	color = 0;
	t = game->textures;
	frame = game->enemies[ray->enemy_id]->frame;
	bpp = t->enemy[ray->enemy_type][frame].bits_per_pixel;
	len = t->enemy[ray->enemy_type][frame].line_len;
	color = *(int*)&t->enemy[ray->enemy_type][frame].pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	if (color == 6517885)
		return (-1);
	return (color);
}

void	draw_enemy(t_game *game, int x, t_raycaster *ray)
{
	int		color;

	float	tex_y;
	float	step;
	t_point	top;
	t_point	bottom;
	int		enemy_height;
	float	distance_factor;
	int		enemy_scale;


	distance_factor = 1.0f / ray->distance_enemy;
	if (ray->enemy_type == OFFICER)
		enemy_scale = 5000;
	else if (ray->enemy_type == BOSS)
		enemy_scale = 8000;
	else
		enemy_scale = 10000;
	enemy_height = enemy_scale * distance_factor;
	bottom.y = HEIGHT * 0.5f + 8000 * distance_factor + game->player->jump_height;
	top.y = bottom.y - 2 * enemy_height;
	tex_y = 0;
	step = (float)game->textures->enemy[ray->enemy_type][0].height / (bottom.y - top.y);
	while (top.y < bottom.y)
	{
		color = get_enemy_color(game, ray, ray->tex_x, tex_y);
		if (color != -1)
		{
			// printf("HERE\n");
			put_pixel_to_img(game, x, top.y, color);
		}
		top.y++;
		tex_y += step;
	}
}


void	animate_sprites(t_game *game)
{
	int	i;
	static int frame = 0;
	static int counter = 0;

	i = 0;
	while (i < game->enemy_count)
	{
		game->enemies[i]->frame = frame;
		i++;
	}
	if (++counter == ANIMATION_SPEED)
	{
		frame = (frame + 1) % 4;
		counter = 0;
	}
	move_sprites(game);
}

float	distance(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrtf(dx * dx + dy * dy));
}

void	move_sprites(t_game *game)
{
	t_enemy	**enemy;
	t_point	new_pos;
	int		wall_in_x;
	int		wall_in_y;
	int	i;

	enemy = game->enemies;
	i = 0;
	while (i < game->enemy_count)
	{
		new_pos.x = enemy[i]->pos.x + (enemy[i]->speed * enemy[i]->dir_vec.x);
		new_pos.y = enemy[i]->pos.y + (enemy[i]->speed * enemy[i]->dir_vec.y);
		if (distance(new_pos.x, new_pos.y, game->player->pos.x, game->player->pos.y) < 10)
			return (player_dead(game));
		wall_in_x = game->map->map[(int)(enemy[i]->pos.y / SCALE)][(int)(new_pos.x / SCALE)] == WALL
				|| game->map->map[(int)(enemy[i]->pos.y + PSIZE) / SCALE][((int)(new_pos.x + PSIZE)) / SCALE] == WALL
				|| game->map->map[(int)(enemy[i]->pos.y + PSIZE) / SCALE][(int)new_pos.x / SCALE] == WALL
				|| game->map->map[(int)(enemy[i]->pos.y) / SCALE][((int)new_pos.x + PSIZE) / SCALE] == WALL;

		wall_in_y = game->map->map[(int)(new_pos.y / SCALE)][(int)(enemy[i]->pos.x / SCALE)] == WALL
				|| game->map->map[(int)(new_pos.y + PSIZE) / SCALE][(int)(enemy[i]->pos.x + PSIZE) / SCALE] == WALL
				|| game->map->map[(int)(new_pos.y + PSIZE) / SCALE][(int)enemy[i]->pos.x / SCALE] == WALL
				|| game->map->map[(int)(new_pos.y) / SCALE][((int)enemy[i]->pos.x + PSIZE) / SCALE] == WALL;
		if (!wall_in_x && !wall_in_y)
		{
			enemy[i]->pos.y = new_pos.y;
			enemy[i]->pos.x = new_pos.x;
		}
		else if (!wall_in_x)
			enemy[i]->pos.x = new_pos.x;
		else if (!wall_in_y)
			enemy[i]->pos.y = new_pos.y;
		enemy[i]->left.x = enemy[i]->pos.x - enemy[i]->dir_vec.y * ESIZE / 2;
		enemy[i]->left.y = enemy[i]->pos.y + enemy[i]->dir_vec.x * ESIZE / 2;
		enemy[i]->right.x = enemy[i]->pos.x + enemy[i]->dir_vec.y * ESIZE / 2;
		enemy[i]->right.y = enemy[i]->pos.y - enemy[i]->dir_vec.x * ESIZE / 2;
		i++;
	}
}
