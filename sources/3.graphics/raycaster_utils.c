#include "../../includes/cub3d.h"

void	render_rayimage(t_game *game, int start_x, int start_y, int color)
{
	int	width;
	int	height;

	width = WIDTH;
	height = HEIGHT;
	for (int y = start_y; y < start_y + height; y++)
	{
		for (int x = start_x; x < start_x + width; x++)
			put_pixel_to_img(game, x, y, color);
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

int	get_texture_color(t_game *game, int tex_x, int tex_y)
{
	int			color;
	int			bpp;
	int			len;
	t_textures	*t;

	color = 0;
	t = game->textures;
	bpp = t->north.bits_per_pixel;
	len = t->north.line_len;

	if (game->dir == N_)
		color = *(int*)&t->north.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	else if (game->dir == S_)
		color = *(int*)&t->south.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	else if (game->dir == W_)
		color = *(int*)&t->west.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	else
		color = *(int*)&t->east.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
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