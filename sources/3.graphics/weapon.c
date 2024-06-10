#include "../../includes/cub3d.h"

int	get_weapon_color(t_game *game, int tex_x, int tex_y, int frame)
{
	int			color;
	int			bpp;
	int			len;
	int		w_type;
	t_textures	*t;

	color = 0;
	w_type = game->player->weapon;
	t = game->textures;
	bpp = t->weapon[w_type][frame].bits_per_pixel;
	len = t->weapon[w_type][frame].line_len;
	color = *(int*)&t->weapon[w_type][frame].pixels_ptr[tex_x * (bpp / 8) + (tex_y * len)];
	// printf("%d\n", *(int*)&t->weapon[w_type][frame].pixels_ptr[5* (bpp / 8) + (5 * len)]);
	if (color == 9961608 || color == 33023)	//removing background
		return (-1);
	return (color);
}

void	draw_weapon(t_game *game, int frame)
{
	int		x;
	int		y;
	int		tex_y;
	int		tex_x;
	int 	color;
	int		scale;
	int		w_type;
	t_img	(*weapon)[5];

	scale = 8;
	w_type = game->player->weapon;
	weapon = game->textures->weapon;
	y = HEIGHT - weapon[w_type][frame].height * scale;
	tex_y = 0;
	while (y < HEIGHT)
	{
		x = (WIDTH / 2) - (weapon[w_type][frame].width * scale / 2);
		tex_x = 0;
		while (x < (WIDTH / 2) + (weapon[w_type][frame].width * scale / 2))
		{
			color = get_weapon_color(game, tex_x, tex_y, frame);
			if (color != -1)
				put_pixel_to_img(game, x, y, color);
			x++;
			if (x % scale == 0)
				tex_x++;
		}
		y++;
		if (y % scale == 0)
			tex_y++;
	}
}

void	render_weapon(t_game *game)
{
	int	*frame;

	frame = &game->player->shooting;
	if (*frame)
	{
		if (*frame < SHOOT_SPEED * 5)
		{
			draw_weapon(game, *frame / SHOOT_SPEED);
			(*frame)++;
		}
		else
			*frame = 0;
	}
	else
		draw_weapon(game, *frame);
}
