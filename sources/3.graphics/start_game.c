#include "../../includes/cub3d.h"

void	init_mlx_window(t_game *game, t_map *map)
{
	game->map = map;
	game->mlx = mlx_init();
	if (!game->mlx)
		free_map(map, "Failed to init mlx", 1);

	game->width = map->max_coll * SCALE;	// change this scale after aplying raycasting
	game->heigth = map->rows * SCALE;
	game->win = mlx_new_window(game->mlx, game->width, game->heigth, "cub3D");
}

void	start_game(t_map *map)
{
	t_game	game;

	init_mlx_window(&game, map);
	// render_game(&game);
	mlx_loop(game.mlx);
}
