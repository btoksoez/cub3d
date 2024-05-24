#ifndef DEFINE_H
# define DEFINE_H

#ifdef LINUX
/* ----------------- Linux---------------- */
# include "./minilibx-linux/mlx.h"
#else
/* ------------------ Mac ----------------- */
# include "./minilibx-mac/mlx.h"
#endif

//we should use keysym instead, more portable

/* --------------- General --------------- */
# define WHITESPACE " \t\n\r\f\v"
# define VALID_CHARS "NSEW01 \t\n\r\f\v\0"
# define WS_COMMA " \t\n\r\f\v,"
# define QUIT 1
/* -------------- PI Values -------------- */
# define PI 3.141592653f
# define PI_05 (PI / 2.0)
# define PI_15 (3.0 * PI / 2.0)
/* -------------- Directions ------------- */
# define NORTH PI_15
# define SOUTH PI_05
# define EAST 0
# define WEST PI
/* -------------- Movements ------------- */
# define UP 1
# define RIGHT 1
# define LEFT -1
# define DOWN -1
# define RESET 0
/* ----------------- Game ---------------- */
# define PLAYER "NSEW"
# define SCALE 50
# define PSIZE SCALE / 4
# define PCENTER PSIZE / 2
# define MOVE 3
# define ROT_SPEED 0.05
# define BUFFER 10
# define WALL 49
# define VISITED 85
# define ENEMY 88
# define EMPTY 48
# define WON 89
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
# define GREY 0xFF8080
/* ---------------- Images --------------- */
# define SCREEN GREY
# define SPACE WHITE
# define WALLS ORANGE
# define PLAYER_ BLUE

#endif
