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
	check_movements(game);

	render_2dgame(game);
	raycast(game);

	// minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mapwin, game->mapimg.img_ptr, 0, 0);
	return (0);
}
