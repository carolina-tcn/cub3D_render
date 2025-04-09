#include "cub3d.h"

//DEFINING PROJECTION ATTRIBUTES
void	init_player(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->direction_x = 0;
		player->direction_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (dir == 'S')
	{
		player->direction_x = 0;
		player->direction_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (dir == 'E')
	{
		player->direction_x = 1;
		player->direction_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->direction_x = -1;
		player->direction_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

//🔦 STEP 3: FINDING WALLS (LANZAR RAYOS)
void	init_ray(t_ray *ray, t_player *player, int x)
{//camera_x ajusta el ángulo del rayo.
	double	camera_x = 2 * x / (double)WIN_WIDTH - 1;
		// Dirección del rayo
	ray->ray_dir_x = player->direction_x + player->plane_x * camera_x;
	ray->ray_dir_y = player->direction_y + player->plane_y * camera_x;

		// Posición inicial del rayo
	ray->ray_pos_x = player->position_x;
	ray->ray_pos_y = player->position_y;

	ray->ray_map_x = (int)ray->ray_pos_x;
	ray->ray_map_y = (int)ray->ray_pos_y;

			// Calcular delta_dist con protección
	if (ray->ray_dir_x != 0)
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	else
		ray->delta_dist_x = INFINITY;
	if (ray->ray_dir_y != 0)
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	else
		ray->delta_dist_y = INFINITY;
}