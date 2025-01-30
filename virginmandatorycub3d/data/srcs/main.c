/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:44:42 by fparis            #+#    #+#             */
/*   Updated: 2025/01/29 15:01:43 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	move(data);
	get_all_rays(data);
	show_screen(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	if (!parsing(argc, argv, &data))
		exit_free(&data, "Parsing error");
	if (!check_textures(data.wall_tex))
		exit_free(&data, "Cannot create texture");
	init_player(&data);
	mlx_set_fps_goal(data.mlx, FPS_CAP);
	init_mlx_events(&data);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);
	free_data(&data);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (0);
}
