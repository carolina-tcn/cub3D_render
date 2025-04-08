/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:32:00 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/04/06 13:24:24 by borjamc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Hook para MLX
void game_loop(void *param)
{
	render_frame((mlx_image_t *)param);
}

//mlx_t* is a struct containing the current window instance

int main(void)
{
	mlx_t *mlx = NULL;
	mlx_image_t *img = NULL;

	//	Initialize and run a new window instance.
	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D - Raycasting Test", true);
	if (!mlx)
	{
		printf("MLX init error\n");
		exit(EXIT_FAILURE);
	}
	// Crear imagen
	img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	// Display an instance of the image
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	{
		printf("Image error\n");
		exit(EXIT_FAILURE);
	}

	// Dibujar un primer frame
	mlx_loop_hook(mlx, game_loop, img);
	mlx_loop(mlx); //Keep the window open as long as a shutdown is not requested.
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx); // Destroy and clean up all images and mlx resources.
	return (EXIT_SUCCESS);
}