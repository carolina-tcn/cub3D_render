#ifndef CUB3D_H
# define CUB3D_H

# include <libft/libft.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include "MLX42/MLX42.h"
# include "test.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 400
# define TILE 64

typedef struct  s_player
{
    double  position_x;
    double  position_y;
    double  direction_x;
    double  direction_y;
    double  plane_x;
    double  plane_y;
}   t_player;

typedef struct  s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;

	// Posición del rayo (normalmente empieza en pos del jugador)
	double	ray_pos_x;
	double	ray_pos_y;

	// Cuadrícula del mapa donde está el rayo
	int		ray_map_x;
	int		ray_map_y;

	// Delta distances (avance entre líneas de grid)
	double	delta_dist_x;
	double	delta_dist_y;

	// Lados iniciales
	double	side_dist_x;
	double	side_dist_y;

	// Hacia qué lado va a moverse en el grid
	int		step_x;
	int		step_y;

	// 0 si golpea pared vertical, 1 si horizontal
	int		side;

	// Distancia perpendicular al muro
	double  perp_wall_dist;

	// Para la altura de la línea a pintar (más adelante)
	int		line_height;
	int		draw_start;
	int		draw_end;
}   t_ray;

//mlx_t* is a struct containing the current window instance
typedef struct  s_data
{
    mlx_t       *mlx;
    mlx_image_t *img;    
    t_player    player;
}   t_data;

void    init_player(t_player *player, char dir);
void	init_ray(t_ray *ray, t_player *player, int x);
void	calculate_step_and_side_dist(t_ray *ray);
void	perform_dda(t_ray *ray);
void	calculate_projection(t_ray *ray);
void	render_frame(t_data *data);
void	game_loop(void *param);

void    key_handler(mlx_key_data_t keydata, void *param);

#endif