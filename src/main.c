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
void	game_loop(void *param)
{
	t_data	*data = (t_data *)param;
	render_frame(data);
}

int	main(void)
{
	t_data	data;

	//init data

	//	Initialize and run a new window instance.
	data.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D - Raycasting Test", true);
	if (!data.mlx)
	{
		printf("MLX init error\n"); //gestionar ERRORES
		exit(EXIT_FAILURE);
	}
	// Crear imagen
	data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	// Display an instance of the image
	if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
	{
		printf("Image error\n");  //gestionar ERRORES
		mlx_terminate(data.mlx);
		exit(EXIT_FAILURE);
	}

	//PARTE HARDCODEADA PLAYER Y MAP
	data.player.position_x = player_x;
	data.player.position_y = player_y;
	init_player(&data.player, player_dir);

	// hook bucle juego
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx); //Keep the window open as long as a shutdown is not requested.
	
	//clean all, clean data
	mlx_delete_image(data.mlx, data.img);
	mlx_terminate(data.mlx); // Destroy and clean up all images and mlx resources.
	return (EXIT_SUCCESS);
}