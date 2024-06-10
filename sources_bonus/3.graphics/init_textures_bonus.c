#include "../../includes_bonus/cub3d.h"

void	init_texture(t_game *game, t_img *texture_img, char *texture)
{
	texture_img->img_ptr = mlx_xpm_file_to_image(game->mlx, texture, &texture_img->width, &texture_img->height);
	if (!texture_img->img_ptr)
	{
		mlx_destroy_window(game->mlx, game->win);
		// mlx_destroy_display(game->mlx);
		free(game->mlx);
		free_map(game->map, "Failed to initialize texture", 1);
	}
	texture_img->pixels_ptr = mlx_get_data_addr(texture_img->img_ptr,
												&texture_img->bits_per_pixel,
												&texture_img->line_len,
												&texture_img->endian);
}

void	init_textures(t_game *game, t_textures *textures)
{
	init_texture(game, &textures->north, game->map->no_texture);
	init_texture(game, &textures->south, game->map->so_texture);
	init_texture(game, &textures->east, game->map->ea_texture);
	init_texture(game, &textures->west, game->map->we_texture);
	init_texture(game, &textures->aim, "./textures/aim.xpm");
	init_texture(game, &textures->map, "./textures/map.xpm");
	init_texture(game, &textures->ground, "./textures/floor.xpm");
	init_texture(game, &textures->sky, "./textures/sky.xpm");
	init_texture(game, &textures->weapon[0][0], "./textures/gun/gun1.xpm");
	init_texture(game, &textures->weapon[0][1], "./textures/gun/gun2.xpm");
	init_texture(game, &textures->weapon[0][2], "./textures/gun/gun3.xpm");
	init_texture(game, &textures->weapon[0][3], "./textures/gun/gun4.xpm");
	init_texture(game, &textures->weapon[0][4], "./textures/gun/gun5.xpm");
	init_texture(game, &textures->weapon[1][0], "./textures/knife/knife1.xpm");
	init_texture(game, &textures->weapon[1][1], "./textures/knife/knife2.xpm");
	init_texture(game, &textures->weapon[1][2], "./textures/knife/knife3.xpm");
	init_texture(game, &textures->weapon[1][3], "./textures/knife/knife4.xpm");
	init_texture(game, &textures->weapon[1][4], "./textures/knife/knife5.xpm");
	init_texture(game, &textures->weapon[2][0], "./textures/mg/mg1.xpm");
	init_texture(game, &textures->weapon[2][1], "./textures/mg/mg2.xpm");
	init_texture(game, &textures->weapon[2][2], "./textures/mg/mg3.xpm");
	init_texture(game, &textures->weapon[2][3], "./textures/mg/mg4.xpm");
	init_texture(game, &textures->weapon[2][4], "./textures/mg/mg5.xpm");
	init_texture(game, &textures->weapon[3][0], "./textures/sticks/sticks1.xpm");
	init_texture(game, &textures->weapon[3][1], "./textures/sticks/sticks2.xpm");
	init_texture(game, &textures->weapon[3][2], "./textures/sticks/sticks3.xpm");
	init_texture(game, &textures->weapon[3][3], "./textures/sticks/sticks4.xpm");
	init_texture(game, &textures->weapon[3][4], "./textures/sticks/sticks5.xpm");
	init_texture(game, &textures->enemy[0][0], "./textures/officer/officer1.xpm");
	init_texture(game, &textures->enemy[0][1], "./textures/officer/officer2.xpm");
	init_texture(game, &textures->enemy[0][2], "./textures/officer/officer3.xpm");
	init_texture(game, &textures->enemy[0][3], "./textures/officer/officer4.xpm");
	init_texture(game, &textures->enemy[1][0], "./textures/boss/boss1.xpm");
	init_texture(game, &textures->enemy[1][1], "./textures/boss/boss2.xpm");
	init_texture(game, &textures->enemy[1][2], "./textures/boss/boss3.xpm");
	init_texture(game, &textures->enemy[1][3], "./textures/boss/boss4.xpm");
	init_texture(game, &textures->enemy[2][0], "./textures/rat/rat1.xpm");
	init_texture(game, &textures->enemy[2][1], "./textures/rat/rat2.xpm");
	init_texture(game, &textures->enemy[2][2], "./textures/rat/rat3.xpm");
	init_texture(game, &textures->enemy[2][3], "./textures/rat/rat4.xpm");
	game->textures = textures;
}
