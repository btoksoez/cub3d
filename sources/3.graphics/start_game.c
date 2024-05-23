#include "../../includes/cub3d.h"

void put_pixel_to_img(t_game *game, int x, int y, int color)
{
    if (x >= 0 && x < game->width && y >= 0 && y < game->height)
    {
        int offset = (y * game->img.line_len) + (x * (game->img.bits_per_pixel / 8));
        *(unsigned int *)(game->img.pixels_ptr + offset) = color;
    }
}


void draw_rectangle(t_game *game, int start_x, int start_y, int width, int height, int color)
{
    for (int y = start_y; y < start_y + height; y++)
    {
        for (int x = start_x; x < start_x + width; x++)
        put_pixel_to_img(game, x, y, color);
    }
}

void draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color)
{
    // Bresenham's line algorithm
    int dx = abs(end_x - start_x);
    int dy = abs(end_y - start_y);
    int sx = (start_x < end_x) ? 1 : -1;
    int sy = (start_y < end_y) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        put_pixel_to_img(game, start_x, start_y, color);

        if (start_x == end_x && start_y == end_y)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            start_x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            start_y += sy;
        }
    }
}

void draw_player(t_game *game, int start_x, int start_y, int width, int height, int color)
{
	for (int y = start_y; y < start_y + height; y++)
	{
		for (int x = start_x; x < start_x + width; x++)
			put_pixel_to_img(game, x, y, color);
	}
	// Draw the viewing direction line
	int line_length = 50; // Change this to control the length of the line
	int end_x = (start_x + PSIZE / 2) + line_length * cos(game->player_angle);
	int end_y = (start_y + PSIZE / 2) + line_length * sin(game->player_angle);
	draw_line(game, (start_x + PSIZE / 2), (start_y + PSIZE / 2), end_x, end_y, color);
}

//somehow need to scale map to screensize, so that for any map, the screensize if still 1080 x 720
void	render_2dgame(t_game *game)
{
	draw_rectangle(game, 0, 0, game->width, game->height, BLACK);

	for (int y = 0; y < game->map->rows; y++)
	{
		for (int x = 0; x < game->map->max_coll; x++)
		{
			if (game->map->map[y][x] == WALL)
				draw_rectangle(game, x * SCALE, y * SCALE, SCALE, SCALE, GREEN);
			if (game->map->map[y][x] == EMPTY)
				draw_rectangle(game, x * SCALE, y * SCALE, SCALE, SCALE, BLUE);
			draw_player(game, game->player_x, game->player_y, PSIZE, PSIZE, YELLOW);
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
