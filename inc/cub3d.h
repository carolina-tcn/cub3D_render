#ifndef CUB3D_H
# define CUB3D_H

# include <libft/libft.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "MLX42/MLX42.h"
# include "test.h"

#define WIN_WIDTH 320
#define WIN_HEIGHT 200

typedef struct  s_player
{
    double  position_x;
    double  position_y;
    double  direction_x;
    double  direction_y;
    double  plane_x;
    double  plane_y;
}   t_player;

typedef struct s_ray
{
    double  ray_dir_x;
    double  ray_dir_y;
    double  camera_x;
}   t_ray;

typedef struct  s_data
{
    mlx_t			*mlx;
    mlx_image_t		*img;    
    t_player    player;
}   t_data;


#endif