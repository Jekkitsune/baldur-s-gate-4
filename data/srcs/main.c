/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:44:42 by fparis            #+#    #+#             */
/*   Updated: 2024/10/13 09:52:04 by gmassoni         ###   ########.fr       */
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
	camera_move(data);
	if (data->player.focus_mode)
		rotate_focus(data);
	if (data->on_screen)
		mlx_mouse_move(data->mlx, data->win, data->win_size.x / 2, data->win_size.y / 2);

	if (data->test_key)
	{
		data->test_key = 0;
		data->player.focus_mode = !data->player.focus_mode; 
		if (data->player.focus_mode)
		{
			data->player.focus_dist = 40;
			data->player.target_pos = data->player.pos;
			data->player.target_offset = data->player.offset;
		}
		else
		{
			data->player.pos = data->player.target_pos;
			data->player.offset = data->player.target_offset;
			data->player.height = 0;
			data->player.pitch = 0;
		}
	}
	move(data);
	update_chunk(data);
	show_screen(data);
	show_minimap(data);

	//show_tex(data, data->textures[2], vec(100, 100));
	//show_tex(data, data->textures[0], vec(100, 100));
	//show_tex(data, data->textures[1], vec(100 + data->textures[0]->size, 100));

	struct timeval 	tv;
	gettimeofday(&tv, NULL);
	newtime = tv.tv_sec;
	if (newtime > starttime)
	{
		printf("%zu\n", frame);
		if (frame == 0)
			frame = 1;
		data->player.speed = (double) 1 / ((double) frame / (double) 60);
		frame = 0;
		starttime = newtime;
	}
	frame++;

	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	if (!parsing(argc, argv, &data))
		return (false);
	if (!check_textures(data.textures))
	{
		//free all
		ft_putstr_fd("Cannot create texture\n", 2);
		return (1);
	}

	init_player(&data);

	create_minimap(&data, 200, 30);

	//mlx_set_fps_goal(data.mlx, 60);
	mlx_on_event(data.mlx, data.win, MLX_KEYDOWN, key_down_manager, &data);
	mlx_on_event(data.mlx, data.win, MLX_KEYUP, key_up_manager, &data);
	mlx_on_event(data.mlx, data.win, MLX_WINDOW_EVENT, window_manager, &data);
	
	update_chunk(&data);
	//print_map(data.current_map);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_mouse_move(data.mlx, data.win, data.win_size.x / 2, data.win_size.y / 2);
	mlx_loop(data.mlx);


	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	//free(data.current_map);
	for (int i = 0; i < data.win_size.y; i++)
		free(data.screen_buffer[i]);
	free(data.screen_buffer);
	return (0);
}
