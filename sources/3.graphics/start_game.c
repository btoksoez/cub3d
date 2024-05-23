#include "../../includes/cub3d.h"

void put_pixel_to_img(t_game *game, int x, int y, int color)
{
    if (x >= 0 && x < game->width && y >= 0 && y < game->height) {
        int offset = (y * game->img.line_len) + (x * (game->img.bits_per_pixel / 8));
        *(unsigned int *)(game->img.pixels_ptr + offset) = color;
    }
}


void draw_rectangle(t_game *game, int start_x, int start_y, int width, int height, int color)
{
    for (int y = start_y; y < start_y + height; y++) {
        for (int x = start_x; x < start_x + width; x++) {
            put_pixel_to_img(game, x, y, color);
        }
    }
}

void draw_player(t_game *game, int start_x, int start_y, int width, int height, int color)
{
    for (int y = start_y; y < start_y + height; y++) {
        for (int x = start_x; x < start_x + width; x++) {
            put_pixel_to_img(game, x, y, color);
        }
    }
}


//somehow need to scale map to screensize, so that for any map, the screensize if still 1080 x 720
void	render_2dgame(t_game *game)
{
	draw_rectangle(game, 0, 0, game->width, game->height, BLACK);

    int start_x = (game->width - game->map->max_coll * SCALE) / 2;
    int start_y = (game->height - game->map->rows * SCALE) / 2;

    for (int y = 0; y < game->map->rows; y++)
    {
        for (int x = 0; x < game->map->max_coll; x++)
        {
            if (game->map->map[y][x] == WALL)
                draw_rectangle(game, start_x + x * SCALE, start_y + y * SCALE, SCALE, SCALE, GREEN);
            if (game->map->map[y][x] == EMPTY || ft_strchr(PLAYER, game->map->map[y][x]))
                draw_rectangle(game, start_x + x * SCALE, start_y + y * SCALE, SCALE, SCALE, BLUE);
            if (ft_strchr(PLAYER, game->map->map[y][x]))
                draw_player(game, start_x + x * SCALE + SCALE / 3, start_y + y * SCALE + SCALE / 3, 0.3 * SCALE, 0.3 * SCALE, YELLOW);
        }
    }
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}

void	start_game(t_map *map)
{
	t_game	game;

	init_mlx(&game, map);
	render_2dgame(&game);
	mlx_loop(game.mlx);
}
