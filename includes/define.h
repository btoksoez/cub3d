#ifndef DEFINE_H
# define DEFINE_H

/* ----------------- Linux---------------- */
// # include "./minilibx-linux/mlx.h"
// # define ESC 65307
// # define W 119
// # define A 97
// # define S 115
// # define D 100
// # define UP 65362
// # define LEFT 65361
// # define RIGHT 65363
// # define DOWN 65364
/* ------------------ Mac ----------------- */
# include "./minilibx-mac/mlx.h"
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define LEFT 123
# define RIGHT 124
# define DOWN 125

/* --------------- General --------------- */
# define WHITESPACE " \t\n\r\f\v"
# define VALID_CHARS "NSEW01 \t\n\r\f\v\0"
# define WS_COMMA " \t\n\r\f\v,"
/* -------------- PI Values -------------- */
# define PI 3.141592653f
# define PI_05 (PI / 2.0)
# define PI_15 (3.0 * PI / 2.0)
/* -------------- Directions ------------- */
# define NORTH PI_15
# define SOUTH PI_05
# define EAST 0
# define WEST PI
/* ----------------- Hooks --------------- */
# define KeyPress 2
# define DestroyNotify 17
# define KeyPressMask 1L << 0
# define StructureNotifyMask 1L << 17
/* ----------------- Game ---------------- */
# define PLAYER "NSEW"
# define MOVE 10
# define BUFFER 10
# define WALL 49
# define VISITED 85
# define ENEMY 88
# define EMPTY 48
# define WON 89
# define SCALE 50
# define PSIZE 15
# define WIDTH 1080
# define HEIGHT 720
/* ---------------- Colors --------------- */
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define ORANGE 0xFF4500
/* ---------------- Images --------------- */
# define SCREEN BLACK
# define SPACE WHITE
# define WALLS ORANGE
# define PLAYER_ BLUE

#endif
