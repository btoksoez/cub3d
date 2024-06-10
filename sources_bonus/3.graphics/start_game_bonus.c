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
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}

void	player_dead(t_game *game)
{
	game->is_player_dead = true;
}
