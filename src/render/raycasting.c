#include "cub3d.h"

//tan(fov / 2) ≈ tan(33°) ≈ 0.66
//FOV = 60° → tan(30°) = ~0.577
//FOV = 66° → tan(33°) = ~0.649 → se redondea a 0.66 por comodidad

//inicializo a partir del player en el mapa, su direccion y su plano, FOV = 60 grados
//una vez recorrido el mapa tendremos coordenadas xy del player y calular
//player_x = x + 0.5;
//player_y = y + 0.5;



void	calculate_step_and_side_dist(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->ray_pos_x - ray->ray_map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->ray_map_x + 1.0 - ray->ray_pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->ray_pos_y - ray->ray_map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->ray_map_y + 1.0 - ray->ray_pos_y) * ray->delta_dist_y;
	}
}
//Se usa DDA para detectar colisiones con muros.
void	perform_dda(t_ray *ray)
{
	int hit = 0;

	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->ray_map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->ray_map_y += ray->step_y;
			ray->side = 1;
		}
		if (g_map[ray->ray_map_y][ray->ray_map_x] == '1')
			hit = 1;
	}
}
//📏 STEP 4: FINDING DISTANCE TO WALLS
void	calculate_projection(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->ray_map_x - ray->ray_pos_x + (1.0 - ray->step_x) / 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->ray_map_y - ray->ray_pos_y + (1.0 - ray->step_y) / 2.0) / ray->ray_dir_y;

	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
		//STEP 5: DRAWING WALLS
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);

	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;

	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

