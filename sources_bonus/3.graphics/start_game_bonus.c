#include "../../includes_bonus/cub3d.h"

void	start_game(t_map *map)
{
	t_game		game;
	t_player	player;
	t_textures	textures;

	init_mlx(&game, &textures, &player, map);
	mlx_loop_hook(game.mlx, &render, &game);
	mlx_loop(game.mlx);
}

int	get_aim_color(int tex_x, int tex_y, t_textures *texture)
{
	int	color;
	int	bpp;
	int	len;

	bpp = texture->aim.bits_per_pixel;
	len = texture->aim.line_len;

	if (tex_x < 0 || tex_x >= texture->aim.width || tex_y < 0 || tex_y >= texture->aim.height)
		return (0);

	color = *(int*)&texture->aim.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	return (color);
}

void	aim(t_game *game)
{
	t_textures	*texture;
	int			color;
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;

	texture = game->textures;
	y = (HEIGHT / 2) - (HEIGHT / 20);
	while (y < (HEIGHT / 2) + (HEIGHT / 20))
	{
		x = (WIDTH / 2) - (WIDTH / 20);
		while (x < (WIDTH / 2) + (WIDTH / 20))
		{
			tex_x = x - (WIDTH / 2) + (texture->aim.width / 2);
			tex_y = y - (HEIGHT / 2) + (texture->aim.height / 2);
			color = get_aim_color(tex_x, tex_y, texture);

			if (!((color >> 24) & 0xFF))
				put_pixel_to_img(game, x, y, color);
			x++;
		}
		y++;
	}
}


int	render(t_game *game)
{
	t_raycaster ray;

	if (game->is_player_dead)
		return (0);

	check_movements(game);
	get_enemy_positions(game);
	animate_sprites(game);
	raycast(game, &ray);
	render_weapon(game);
	minimap(game, &ray);
	aim(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}

void	player_dead(t_game *game)
{
	game->is_player_dead = true;
}
