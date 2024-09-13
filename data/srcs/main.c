/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:44:42 by fparis            #+#    #+#             */
/*   Updated: 2024/09/12 22:56:46 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned long	frame = 0;
unsigned long	starttime;
unsigned long	newtime;

int	loop(void *param)
{
	t_data *data;

	data = (t_data *)param;
	move(data);
	if (data->test_key)
	{
		data->test_key = 0;
		data->scale++;
	}
	//mlx_clear_window(data->mlx, data->win);
	update_chunk(data);
	show_screen(data);
	show_minimap(data);

	struct timeval 	tv;
	gettimeofday(&tv, NULL);
	newtime = tv.tv_sec;
	if (newtime > starttime)
	{
		printf("%zu\n", frame);
		frame = 0;
		starttime = newtime;
	}
	frame++;

	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	struct timeval tv;
	gettimeofday(&tv, NULL);
	starttime = tv.tv_sec;

	if (argc < 2)
	{
		ft_putstr_fd("Not enough maps!\n", 2);
		return (1);
	}
	init_data(&data);
	
	data.current_map = create_map(argv[1]);
	print_map(data.current_map);
	printf("\n\n\n\n\n\n\n");
	
	init_player(&data);

	create_minimap(&data, 200, 30);

	//mlx_set_fps_goal(data.mlx, 60);
	mlx_on_event(data.mlx, data.win, MLX_KEYDOWN, key_down_manager, &data);
	mlx_on_event(data.mlx, data.win, MLX_KEYUP, key_up_manager, &data);
	
	update_chunk(&data);
	print_chunk(&data);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);


	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (0);
}
