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

void print_pixels(t_game *game)
{
    int x = 0;
    int y = 0;
	int index = y * game->textures->north.line_len + x * 4;
    unsigned int color = *(unsigned int *)game->textures->east.pixels_ptr[index];
	fprintf(stderr, "Pixel at %d (%d, %d): %u\n", index, x, y, color);
	printf("len: %d, bpp: %d\n", game->textures->east.line_len, game->textures->east.bits_per_pixel);
	int red = (color >> 16) & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = color & 0xFF;
	printf("%d %d %d\n", red, green, blue);
    // while (y < game->textures->east.height) {
    //     x = 0;
    //     while (x < game->textures->east.width) {
    //         int index = y * game->textures->east.line_len + x * (game->textures->east.bits_per_pixel / 8);
    //         color = game->textures->east.pixels_ptr[index];
    //         fprintf(stderr, "Pixel at %d (%d, %d): %d\n", index, x, y, color);
    //         x++;
    //     }
    //     y++;
    // }
}

int	get_texture_color(t_game *game, int tex_x, int tex_y)
{
    int		color;
	int		bpp;
	int		len;
	t_textures *t;

    color = 0;
	t = game->textures;
	bpp = t->north.bits_per_pixel;
	len = t->north.line_len;

	// printf("Line len: %d, bpp: %d\n", t->north.line_len, t->north.bits_per_pixel);
	print_pixels(game);
    if (game->dir == N_)
        color = t->north.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
    else if (game->dir == S_)
        color = t->south.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
    else if (game->dir == W_)
        color = t->west.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
    else
        color = t->east.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
    return (color);
}

void	draw_textures(t_game *game, int start_x, int start_y, int end_x, int end_y)
{
	int		temp;
	int		color;
	float	tex_y;
	float	tex_x;
	float	step;
	(void)	end_x;

	temp = 0;
	if (start_y > end_y)
	{
		temp = start_y;
		start_y = end_y;
		end_y = temp;
	}
	tex_y = 0;
	tex_x = game->textures->north.width * (game->fraction_x + game->fraction_y);
	step = (float)game->textures->north.height / (end_y - start_y);
	while (start_y <= end_y)
	{
		color = get_texture_color(game, tex_x, tex_y);
		put_pixel_to_img(game, start_x, start_y, color);
		start_y++;
		tex_y += step;
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
