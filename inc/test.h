#ifndef TEST_H
# define TEST_H

# define MAP_WIDTH 6
# define MAP_HEIGHT 5

# include "MLX42/MLX42.h"

extern char g_map[MAP_HEIGHT][MAP_WIDTH + 1];
extern int floor_color[3];
extern int ceiling_color[3];
extern float player_x;
extern float player_y;
extern char player_dir;

#endif