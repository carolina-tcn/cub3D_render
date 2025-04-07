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

#include <stdlib.h>
#include <stdio.h>
#include "MLX42/MLX42.h"
#include "test.h"


#define WIN_WIDTH 640
#define WIN_HEIGHT 480



// Hook para MLX
void game_loop(void *param)
{
	render_frame((mlx_image_t *)param);
}

//mlx_t* is a struct containing the current window instance

int main(void)
{
	mlx_t *mlx = NULL;

	//	Initialize and run a new window instance.
	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D - Raycasting Test", true);
	if (!mlx)
	{
		printf("MLX init error\n");
		exit(EXIT_FAILURE);
	}

	mlx_image_t *img = NULL;
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







// // Exit the program as failure.
// static void ft_error(void)
// {
// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

// // Print the window width and height.
// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }

// int	main(void)
// {

// 	// MLX allows you to define its core behaviour before startup.
// 	mlx_set_setting(MLX_MAXIMIZED, true);
// 	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
// 	if (!mlx)
// 		ft_error();

// 	/* Do stuff */

// 	// Create and display the image.
// 	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
// 	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
// 		ft_error();

// 	// Even after the image is being displayed, we can still modify the buffer.
// 	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

// 	// Register a hook and pass mlx as an optional param.
// 	// NOTE: Do this before calling mlx_loop!
// 	mlx_loop_hook(mlx, ft_hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }