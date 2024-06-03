#include "../../includes/cub3d.h"

void	start_game(t_map *map)
{
	t_game		game;
	t_player	player;
	t_textures	textures;

	init_mlx(&game, &textures, &player, map);
	mlx_loop_hook(game.mlx, &render, &game);
	mlx_loop(game.mlx);
}

int	render(t_game *game)
{
	// delete_image?
	hook_player(game);	//sets new pos of player based on u_d, l_r
	render_2dgame(game);
	render_rayimage(game, 0, 0, WHITE);
	cast_rays(game);
	// minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mapwin, game->mapimg.img_ptr, 0, 0);
	return (0);
}

void	render_2dgame(t_game *game)
{
	int			y;
	int			x;
	t_player	*player;

	player = game->player;
	y = 0;
	render_image(game, 0, 0, SCREEN);
	while (y < game->map->rows)
	{
		x = 0;
		while (x < game->map->cols)
		{
			if (game->map->map[y][x] == WALL)
				render_image(game, x * SCALE, y * SCALE, WALLS);
			if (game->map->map[y][x] == EMPTY)
				render_image(game, x * SCALE, y * SCALE, SPACE);
			render_image(game, player->pos.x, player->pos.y, PLAYER_);
			x++;
		}
		y++;
	}
}
// Somehow need to scale map to screensize, so that for any map, the screensize if still 1080 x 720

void	render_rayimage(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;

	width = WIDTH;
	height = HEIGHT;
	for (int y = start_y; y < start_y + height; y++)
	{
		for (int x = start_x; x < start_x + width; x++)
		{
				put_pixel_to_img(game, x, y, color);
		}
	}
}

void	render_image(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;

	if (color == SCREEN)
	{
		width = game->width;
		height = game->height;
	}
	else if (color == PLAYER_)
	{
		width = PSIZE;
		height = PSIZE;
	}
	else
	{
		width = SCALE;
		height = SCALE;
	}
	for (int y = start_y; y < start_y + height; y++)
	{
		for (int x = start_x; x < start_x + width; x++)
		{
			if (x == start_x || x == start_x + width - 1 || y == start_y || y == start_y + height - 1)
				put_pixel_to_mapimg(game, x, y, BLACK);
			else
				put_pixel_to_mapimg(game, x, y, color);
		}
	}
}

void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		int offset = (y * game->img.line_len) + (x * (game->img.bits_per_pixel / 8));
		*(unsigned int *)(game->img.pixels_ptr + offset) = color;
	}
}

void	put_pixel_to_mapimg(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < game->width && y >= 0 && y < game->height)
	{
		int offset = (y * game->mapimg.line_len) + (x * (game->mapimg.bits_per_pixel / 8));
		*(unsigned int *)(game->mapimg.pixels_ptr + offset) = color;
	}
}

void	draw_vline(t_game *game, int start_x, int start_y, int end_x, int end_y, int color)
{
	int	temp;

	temp = 0;
	if (start_y > end_y)
	{
		temp = start_y;
		start_y = end_y;
		end_y = temp;
	}
	while (true)
	{
		put_pixel_to_img(game, start_x, start_y, color);
		if (start_x == end_x && start_y == end_y)
			break ;
		start_y++;
	}
}

int	get_texture_color(t_game *game, int pos, int start_y, int end_y)
{
    int		color;
    int		tex_x;
    float	tex_y;
    double	scale;

    color = 0;
    tex_x = game->textures->width * (int)game->fraction_x / SCALE;
    scale = (pos - start_y) / (end_y - start_y);
    tex_y = (scale * game->textures->height);
    if (game->dir == N_)
        color = game->textures->north.pixels_ptr[tex_x + (int)(tex_y * game->textures->north.line_len)];
    else if (game->dir == S_)
        color = game->textures->south.pixels_ptr[tex_x + (int)(tex_y * game->textures->south.line_len)];
    else if (game->dir == W_)
        color = game->textures->west.pixels_ptr[tex_x + (int)(tex_y * game->textures->west.line_len)];
    else
        color = game->textures->east.pixels_ptr[tex_x + (int)(tex_y * game->textures->east.line_len)];
    return (color);
}

void	draw_textures(t_game *game, int start_x, int start_y, int end_x, int end_y)
{
	int		temp;
	int		color;
	float	pos;
	float	step;

	temp = 0;
	if (start_y > end_y)
	{
		temp = start_y;
		start_y = end_y;
		end_y = temp;
	}
	printf("%d, %d\n", game->textures->height, game->textures->width);
	pos = 0;
	step = (float)game->textures->height / (end_y - start_y);
	while (true)
	{
		color = get_texture_color(game, pos, start_y, end_y);
		put_pixel_to_img(game, start_x, start_y, color);
		if (start_x == end_x && start_y == end_y)
			break ;
		start_y++;
		pos += step;
	}
}

void	draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color)
{
	int dx = abs(end_x - start_x);
	int dy = abs(end_y - start_y);
	int sx = (start_x < end_x) ? 1 : -1;
	int sy = (start_y < end_y) ? 1 : -1;
	int err = dx - dy;

	while (true)
	{
		put_pixel_to_mapimg(game, start_x, start_y, color);
		if (start_x == end_x && start_y == end_y)
			break ;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start_x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start_y += sy;
		}
	}
}

void	draw_point(t_game *game, int x, int y, int color)
{
	int	size;

	size = 6;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			put_pixel_to_mapimg(game, x + i, y + j, color);
	}
}
