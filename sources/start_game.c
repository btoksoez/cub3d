#include "../includes/cub3d.h"

void put_pixel_to_img(t_img *img, int x, int y, int color)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        int offset = (y * img->line_len) + (x * (img->bits_per_pixel / 8));
        *(unsigned int *)(img->pixels_ptr + offset) = color;
    }
}


void draw_rectangle(t_img *img, int start_x, int start_y, int width, int height, int color)
{
    for (int y = start_y; y < start_y + height; y++) {
        for (int x = start_x; x < start_x + width; x++) {
            put_pixel_to_img(img, x, y, color);
        }
    }
}


//somehow need to scale map to screensize, so that for any map, the screensize if still 1080 x 720
void	render_game(t_game *game)
{
	draw_rectangle(&game->img, 0, 0, WIDTH, HEIGHT, RED);

    int map_width = 10;
    int map_height = 9;
    int start_x = (WIDTH - map_width * TILE_SIZE) / 2;
    int start_y = (HEIGHT - map_height * TILE_SIZE) / 2;

    for (int y = 0; y < map_height; y++) {
        for (int x = 0; x < map_width; x++) {
            if (game->map->map[y][x] == '1') {
                draw_rectangle(&game->img, start_x + x * TILE_SIZE, start_y + y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GREEN);
            } else if (game->map->map[y][x] == '0') {
                draw_rectangle(&game->img, start_x + x * TILE_SIZE, start_y + y * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
            }
        }
    }
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}

void	start_game(t_map *map)
{
	t_game	game;

	init(&game, map);
	render_game(&game);
	mlx_loop(game.mlx);
}
