#include "MLX42/MLX42.h"
#include "test.h"
#include <math.h>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

extern mlx_image_t *g_img;

void	render_frame(void)
{
	for (int x = 0; x < WIN_WIDTH; x++)
	{
		// 1. Calcular la dirección del rayo para esta columna
		double camera_x = 2 * x / (double)WIN_WIDTH - 1; // de -1 a 1
		double ray_dir_x;
		double ray_dir_y;

		// Dirección inicial del jugador (según player_dir)
		double dir_x = 0;
		double dir_y = -1;
		double plane_x = 0.66;
		double plane_y = 0;

		if (player_dir == 'N') { dir_x = 0; dir_y = -1; plane_x = 0.66; plane_y = 0; }
		if (player_dir == 'S') { dir_x = 0; dir_y = 1; plane_x = -0.66; plane_y = 0; }
		if (player_dir == 'E') { dir_x = 1; dir_y = 0; plane_x = 0; plane_y = 0.66; }
		if (player_dir == 'W') { dir_x = -1; dir_y = 0; plane_x = 0; plane_y = -0.66; }

		ray_dir_x = dir_x + plane_x * camera_x;
		ray_dir_y = dir_y + plane_y * camera_x;

		// 2. Mapa actual
		int map_x = (int)player_x;
		int map_y = (int)player_y;

		// 3. Calcular delta_dist (distancia entre líneas de grilla)
		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

		// 4. Determinar step y side_dist
		int step_x, step_y;
		double side_dist_x, side_dist_y;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player_x) * delta_dist_x;
		}

		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player_y) * delta_dist_y;
		}

		// 5. DDA: avanzar hasta chocar contra una pared
		int hit = 0;
		int side;
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (g_map[map_y][map_x] == '1')
				hit = 1;
		}

		// 6. Calcular distancia proyectada
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - player_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - player_y + (1 - step_y) / 2) / ray_dir_y;

		// 7. Calcular altura del muro
		int line_height = (int)(WIN_HEIGHT / perp_wall_dist);
		int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		int draw_end = line_height / 2 + WIN_HEIGHT / 2;

		if (draw_start < 0) draw_start = 0;
		if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

		// 8. Dibujar la línea vertical
		for (int y = draw_start; y <= draw_end; y++)
			mlx_put_pixel(g_img, x, y, 0xFFFFFFFF); // blanco por ahora
	}
}
