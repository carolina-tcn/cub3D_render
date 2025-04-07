#ifndef TEST_H
# define TEST_H

# include "MLX42/MLX42.h"
# include <libft/libft.h>
# include <math.h>


# define MAP_WIDTH 6
# define MAP_HEIGHT 5

extern char g_map[MAP_HEIGHT][MAP_WIDTH + 1];
extern int floor_color[3];
extern int ceiling_color[3];
extern float player_x;
extern float player_y;
extern char player_dir;


void render_frame(mlx_image_t *img);


#endif