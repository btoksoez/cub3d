#include "../includes/cub3d.h"

void	put_pixel_to_img(t_game *game, int x, int y)
{
	//placeholder: here read from single imgs to big img
	int	offset;

	offset = (y * game->img.line_len) + (x * (game->img.bits_per_pixel / 8));
	*(unsigned int *)(game->img.pixels_ptr + offset) = RED;
}

void	render_game(t_game *game)
{
	int			x;
	int			y;
	static int	i = 0;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			put_pixel_to_img(game, x, y);	//use this to read from images to img
			x++;
		}
		y++;
	}
	ft_printf("moves: %d\n", i++);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);	//push img to window
}

void	start_game(t_map *map)
{
	t_game	game;


	init(&game, map);
	render_game(&game);
	mlx_loop(game.mlx);
}
