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
	t_raycaster	ray;

	check_movements(game);
	raycast(game, &ray);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	return (0);
}
