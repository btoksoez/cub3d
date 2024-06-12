/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andre-da <andre-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:48:34 by andre-da          #+#    #+#             */
/*   Updated: 2024/06/12 18:28:28 by andre-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub3d_bonus.h"

int	get_img_color(int tex_x, int tex_y, t_img texture)
{
	int	color;
	int	bpp;
	int	len;

	bpp = texture.bits_per_pixel;
	len = texture.line_len;
	if (tex_x < 0 || tex_x >= texture.width || tex_y < 0
		|| tex_y >= texture.height)
		return (0);
	color = *(int *)&texture.pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	return (color);
}

void	draw_texture(t_game *game, int pos_x, int pos_y, t_img texture, int x,
		int y)
{
	int		color;
	float	scale_x;
	float	scale_y;
	float	tex_x;
	float	tex_y;

	scale_x = (float)texture.width / MINI_SCALE;
	scale_y = (float)texture.height / MINI_SCALE;
	tex_x = (int)(x * scale_x) % MINI_SCALE;
	tex_y = (int)(y * scale_y) % MINI_SCALE;
	color = get_img_color((int)tex_x, (int)tex_y, texture);
	if (!((color >> 24) & 0xFF))
		put_pixel_to_img(game, pos_x, pos_y, color);
	x++;
}

void	minimap(t_game *game, t_raycaster *ray)
{
	t_player	*player;
	t_minimap	mini;
	t_textures	*texture;
	int			y;
	int			x;
	int			img_x;
	int			img_y;

	texture = game->textures;
	player = game->player;
	init_minimap(player, &mini);
	img_y = 0;
	y = mini.start_y;
	while (y < mini.end_y)
	{
		get_start_x(player, &mini);
		x = mini.start_x;
		img_x = 0;
		while (x < mini.end_x)
		{
			if (y < (game->map->rows * SCALE))
				if (game->map->map[(int)(y / SCALE)][(int)(x / SCALE)] == WALL)
					draw_texture(game, (mini.start_x - mini.initial_x + (WIDTH - (WIDTH / 5) + (WIDTH / SCALE))), (mini.start_y - mini.initial_y + (HEIGHT - (HEIGHT / 5) + (HEIGHT / SCALE))), texture->north,
						img_x, img_y);
			mini.start_x++;
			x += SCALE_FACTOR;
			img_x++;
		}
		mini.start_y++;
		y += SCALE_FACTOR;
		img_y++;
	}
	render_player_and_rays(game, ray, mini);
}

void	init_minimap(t_player *player, t_minimap *mini)
{
	mini->hori_vision = (SCALE * MINI_COLS / 2) - MINI_PSIZE;
	mini->vert_vision = (SCALE * MINI_ROWS / 2) - MINI_PSIZE;
	mini->start_y = player->pos.y;
	get_start_x(player, mini);
	if (mini->start_y - mini->vert_vision >= 0)
		mini->start_y -= mini->vert_vision;
	else
		mini->start_y = 0;
	mini->end_x = mini->start_x + (SCALE * MINI_COLS);
	mini->end_y = mini->start_y + (SCALE * MINI_ROWS);
	mini->initial_x = mini->start_x;
	mini->initial_y = mini->start_y;
}

void	render_player_and_rays(t_game *game, t_raycaster *ray, t_minimap mini)
{
	t_player	*player;

	player = game->player;
	if ((player->pos.x <= mini.hori_vision)
		&& (player->pos.y <= mini.vert_vision))
		render_player(game, ((WIDTH - (WIDTH / 5) + (WIDTH / SCALE)) + (player->pos.x / 2)), ((HEIGHT - (HEIGHT / 5) + (HEIGHT / SCALE)) + (player->pos.y / 2)));
	else if (player->pos.y <= mini.vert_vision)
		render_player(game, ((WIDTH - (WIDTH / 5) + (WIDTH / SCALE)) + ((MINI_SCALE * 7) / 2) - MINI_PCENTER), ((HEIGHT - (HEIGHT / 5) + (HEIGHT / SCALE)) + (player->pos.y / 2)));
	else if (player->pos.x <= mini.hori_vision)
		render_player(game, ((WIDTH - (WIDTH / 5) + (WIDTH / SCALE)) + (player->pos.x / 2)), ((HEIGHT - (HEIGHT / 5) + (HEIGHT / SCALE)) + ((MINI_SCALE * 5) / 2) - MINI_PCENTER));
	else
		render_player(game, ((WIDTH - (WIDTH / 5) + (WIDTH / SCALE)) + ((MINI_SCALE * 7) / 2) - MINI_PCENTER), ((HEIGHT - (HEIGHT / 5) + (HEIGHT / SCALE)) + ((MINI_SCALE * 5) / 2) - MINI_PCENTER));
	raycast_2d(game, ray, mini);
}

void	render_player(t_game *game, int start_x, int start_y)
{
	int	width;
	int	height;
	int	x;
	int	y;

	width = PSIZE / 2;
	height = PSIZE / 2;
	y = start_y;
	while (y < start_y + height)
	{
		x = start_x;
		while (x < start_x + width)
		{
			put_pixel_to_img(game, x, y, PLAYER_);
			x++;
		}
		y++;
	}
}
