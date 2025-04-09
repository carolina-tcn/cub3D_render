#include "cub3d.h"

uint32_t get_rgba_color(int r, int g, int b)
{
	return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | 0xFF;
}

// Hook para MLX
void	game_loop(void *param)
{
	t_data	*data = (t_data *)param;
	render_frame(data);
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