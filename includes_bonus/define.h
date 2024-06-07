#ifndef DEFINE_H
# define DEFINE_H

#ifdef LINUX
/* ----------------- Linux---------------- */
# include "../includes/minilibx-linux/mlx.h"
#define ESC			65307
#define W			119
#define A			97
#define S			115
#define D			100
#define LEFT_KEY	65361
#define RIGHT_KEY	65363
#define SHIFT		0xFFE1
#define SPACEBAR	0x31
#else
/* ------------------ Mac ----------------- */
# include "../includes/minilibx-mac/mlx.h"
#define ESC			0x35
#define W			0x0D
#define A			0x00
#define S			0x01
#define D			0x02
#define LEFT_KEY	0x7B
#define RIGHT_KEY	0x7C
#define SHIFT		0x101
#define SPACEBAR	0x31
#define LEFT_BTN	0xF0
#define RIGHT_BTN 	0xF1
#define SHOOT		0x03
#define SWITCH		0x0F
#endif
/* --------------- General --------------- */
# define WHITESPACE " \t\n\r\f\v"
# define VALID_CHARS "NSEW01BOH \t\n\r\f\v\0"
# define WS_COMMA " \t\n\r\f\v,"
# define QUIT 1
# define EPSILON 0.0001
/* -------------- PI Values -------------- */
# define PI 3.141592653f
# define PI_05 (PI / 2.0)
# define PI_15 (3.0 * PI / 2.0)
# define PI_2 (2.0 * PI)
/* -------------- Directions ------------- */
# define NORTH PI_15
# define SOUTH PI_05
# define EAST 0
# define WEST PI
# define NORTH_ 0
# define SOUTH_ 1
# define EAST_ 1
# define WEST_ 0
# define NW 1
# define NE 2
# define SW 3
# define SE 4
/* -------------- Movements ------------- */
# define UP 1
# define RIGHT 1
# define LEFT -1
# define DOWN -1
# define RESET 0
/* ----------------- Game ---------------- */
# define PLAYER "NSEW"
# define ENEMY "BOH"
# define SCALE 50
# define PSIZE SCALE / 4
# define PCENTER PSIZE / 2
# define JUMP_SPEED 10
# define MAX_JUMP_HEIGHT 140
# define MAX_JUMP_SPEED 30
# define ROT_SPEED 0.05
# define BUFFER 10
# define WALL 49
# define VISITED 85
# define EMPTY 48
# define WON 89
# define WIDTH 1080
# define HEIGHT 720
# define PLAYER_VISION (PI / 3)
# define WALL_SCALE 8000
# define N_ 0x000000
# define S_ 0xFF4500
# define W_ 0xFFFFFF
# define E_ 0xD63A00
# define GUN 0
# define KNIFE 1
# define SHOOT_SPEED 5
# define OFFICER GREEN
# define BOSS GOLD
# define HITLER PURPLE
/* --------------- Minimap -------------- */
# define MM_WIDTH WIDTH / 5
# define MM_HEIGHT HEIGHT / 5
# define MM_SCALE SCALE / 3
# define MM_SCREEN BLUE

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
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
# define PURPLE 0x800080
# define BROWN 0xA52A2A
# define PINK 0xFFC0CB
# define LIME 0x00FF00
# define GOLD 0xFFD700
# define SILVER 0xC0C0C0
# define INDIGO 0x4B0082
# define TEAL 0x008080
# define MAROON 0x800000
/* ---------------- Images --------------- */
# define SCREEN BLACK
# define SPACE WHITE
# define WALLS ORANGE
# define PLAYER_ BLUE
/* ----------------- Keys ---------------- */
# define KeyPress 2
# define KeyPressMask 1L<<0
# define KeyRelease 3
# define KeyReleaseMask 1L<<1
# define DestroyNotify 17
# define StructureNotifyMask 1L<<17

#endif