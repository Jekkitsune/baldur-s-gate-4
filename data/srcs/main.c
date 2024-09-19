/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:44:42 by fparis            #+#    #+#             */
/*   Updated: 2024/09/19 18:17:28 by gmassoni         ###   ########.fr       */
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
	camera_move(data);
	if (data->player.focus_mode)
		rotate_focus(data);

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
	//mlx_clear_window(data->mlx, data->win);
	if (data->on_screen)
		mlx_mouse_move(data->mlx, data->win, data->win_size.x / 2, data->win_size.y / 2);
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


	init_data(&data);
	
	if (!parsing(argc, argv, &data))
		return (false);
	printf("North Texture: %s\n", data.textures[0]);
	printf("South Texture: %s\n", data.textures[1]);
	printf("West Texture: %s\n", data.textures[2]);
	printf("East Texture: %s\n", data.textures[3]);
	printf("Floor Color: %s\n", data.floor_color);
	printf("Ceiling Color: %s\n", data.ceiling_color);
	for (int i = 0; data.current_map->arr[i]; i++)
		printf("%s\n", data.current_map->arr[i]);
	print_map(data.current_map);

	init_player(&data);

	create_minimap(&data, 200, 30);

	//mlx_set_fps_goal(data.mlx, 60);
	mlx_on_event(data.mlx, data.win, MLX_KEYDOWN, key_down_manager, &data);
	mlx_on_event(data.mlx, data.win, MLX_KEYUP, key_up_manager, &data);
	mlx_on_event(data.mlx, data.win, MLX_WINDOW_EVENT, window_manager, &data);
	
	update_chunk(&data);
	print_chunk(&data);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);


	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.current_map);
	return (0);
}
