#include "cub3d.h"

//tan(fov / 2) ≈ tan(33°) ≈ 0.66
//FOV = 60° → tan(30°) = ~0.577
//FOV = 66° → tan(33°) = ~0.649 → se redondea a 0.66 por comodidad

//inicializo a partir del player en el mapa, su direccion y su plano, FOV = 60 grados
//una vez recorrido el mapa tendremos coordenadas xy del player y calular
//player_x = x + 0.5;
//player_y = y + 0.5;

#include <stdint.h>

uint32_t get_rgba_color(int r, int g, int b)
{
	return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0xFF;
}

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

void	render_frame(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, &data->player, x);
		calculate_step_and_side_dist(&ray);
		perform_dda(&ray);
		calculate_projection(&ray);

		int y = 0;
		uint32_t ceil_color = get_rgba_color(ceiling_color[0], ceiling_color[1], ceiling_color[2]);
		//Dibujar techo
		while (y < ray.draw_start)
		{
			mlx_put_pixel(data->img, x, y, ceil_color);
			y++;
		}
		y = ray.draw_start;
		//Dibujar pared
		while (y < ray.draw_end)
		{
			uint32_t color;
			if (ray.side == 1)
				color = 0xFF0000FF;
			else
				color = 0x880000FF;
			mlx_put_pixel(data->img, x, y, color);
			y++;
		}
		uint32_t floor_col = get_rgba_color(floor_color[0], floor_color[1], floor_color[2]);
		y = ray.draw_end;
		// Dibujar suelo
		while (y < WIN_HEIGHT)
		{
			mlx_put_pixel(data->img, x, y, floor_col);
			y++;
		}
		x++;
	}
}