/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:49:15 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 15:49:16 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

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
	if (tex_x < 0 || tex_x >= texture->aim.width || tex_y < 0
		|| tex_y >= texture->aim.height)
		return (0);
	color = *(int *)&texture->aim.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
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

int	get_map_color(int tex_x, int tex_y, t_textures *texture)
{
	int	color;
	int	bpp;
	int	len;

	bpp = texture->map.bits_per_pixel;
	len = texture->map.line_len;
	if (tex_x < 0 || tex_x >= texture->map.width || tex_y < 0
		|| tex_y >= texture->map.height)
		return (0);
	color = *(int *)&texture->map.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	return (color);
}

void	map(t_game *game)
{
	t_textures	*texture;
	int			color;
	int			x;
	int			y;
	float		scale_x;
	float		scale_y;
	float		tex_x;
	float		tex_y;
	int			mini_width;
	int			mini_height;

	texture = game->textures;
	mini_width = MINI_X_END - MINI_X + 20;
	mini_height = MINI_Y_END - MINI_Y + 30;
	scale_x = (float)texture->map.width / mini_width;
	scale_y = (float)texture->map.height / mini_height;
	y = MINI_Y - 10;
	tex_y = 0;
	while (y < MINI_Y_END)
	{
		x = MINI_X - 10;
		tex_x = 0;
		while (x < MINI_X_END + 10)
		{
			color = get_map_color((int)tex_x, (int)tex_y, texture);
			if (!((color >> 24) & 0xFF))
				put_pixel_to_img(game, x, y, color);
			tex_x += scale_x;
			x++;
		}
		tex_y += scale_y;
		y++;
	}
}

int	render(t_game *game)
{
	t_raycaster	ray;

	if (game->is_player_dead)
		return (0);
	check_movements(game);
	get_enemy_positions(game);
	animate_sprites(game);
	raycast(game, &ray);
	render_weapon(game);
	map(game);
	minimap(game, &ray);
	aim(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}

void	player_dead(t_game *game)
{
	game->is_player_dead = true;
}
