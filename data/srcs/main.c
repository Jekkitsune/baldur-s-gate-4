/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:44:42 by fparis            #+#    #+#             */
/*   Updated: 2024/11/22 19:24:55 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned long	frame = 0;
unsigned long	starttime;
unsigned long	newtime;

int	loop(void *param)
{
	t_data *data;
	int		i;
	int		j;

	data = (t_data *)param;
	camera_move(data);
	if (data->player.focus_mode)
		rotate_focus(data);

	if (data->test_key)
	{
		// if (data->current_map->active_entities)
		//  	remove_active(data, data->current_map->active_entities->content);

		data->test_key = 0;
		t_entity	*entitest;

		entitest = NULL;
		if (in_bound(*data->current_map, data->player.pos) && data->current_map->arr[data->player.pos.x][data->player.pos.y].entities)
			entitest = data->current_map->arr[data->player.pos.x][data->player.pos.y].entities->content;
		if (!data->player.focus_mode && entitest)
			possess(data, entitest);
		else if (data->player.focus_mode)
		{
			unpossess(data);
			remove_arrow(data);
		}
	}

	move(data);
	update_all_active(data);
	update_button_action(data);
	update_chunk(data);
	show_screen(data);
	show_minimap(data);

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
		data->fps = frame;
		data->player.speed = (double) 1 / ((double) data->fps / (double) 60);
		frame = 0;
		starttime = newtime;
	}
	frame++;

	i = 0;
	while (i < data->current_map->size.x)
	{
		j = 0;
		while (j < data->current_map->size.y)
		{
			if (data->current_map->arr[i][j].type == DOOR)
			{
				if (data->current_map->arr[i][j].status == OPENING)
				{
					data->current_map->arr[i][j].timer -= 0.1;
					if (data->current_map->arr[i][j].timer == 0)
						data->current_map->arr[i][j].status = OPEN;
				}
				else if (data->current_map->arr[i][j].status == CLOSING)
				{
					data->current_map->arr[i][j].timer += 0.1;
					if (data->current_map->arr[i][j].timer == 1)
						data->current_map->arr[i][j].status = CLOSE;
				}
			}
			j++;
		}
		i++;
	}

	if (data->current_map->active_entities)
		return (0);
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
	mlx_on_event(data.mlx, data.win, MLX_MOUSEWHEEL, mouse_wheel_manager, &data);
	mlx_on_event(data.mlx, data.win, MLX_WINDOW_EVENT, window_manager, &data);
	mlx_on_event(data.mlx, data.win, MLX_MOUSEDOWN, mouse_down_manager, &data);
	mlx_on_event(data.mlx, data.win, MLX_MOUSEUP, mouse_up_manager, &data);
	
	update_chunk(&data);
	//print_map(data.current_map);
	mlx_loop_hook(data.mlx, loop, &data);

	data.textures[4] = path_to_tex(&data, "image.png");
	data.textures[5] = path_to_tex(&data, "postal.png");
	data.textures[6] = path_to_tex(&data, "wilson_face.png");
	data.textures[7] = path_to_tex(&data, "wilson_side2.png");
	data.textures[8] = path_to_tex(&data, "wilson_back.png");
	data.textures[9] = path_to_tex(&data, "wilson_side.png");
	data.textures[10] = path_to_tex(&data, "s1.png");
	data.textures[11] = path_to_tex(&data, "s2.png");
	data.textures[12] = path_to_tex(&data, "s3.png");
	data.textures[13] = path_to_tex(&data, "s4.png");
	data.textures[14] = path_to_tex(&data, "a.png");
	data.textures[15] = path_to_tex(&data, "b.png");
	data.textures[16] = path_to_tex(&data, "arrow.png");
	data.textures[16]->name = "arrow";
	//add_active(&data, create_entity(&data, vec(25, 10), 1, data.textures[4]), follow_player);
	create_entity(&data, vec(25, 9), data.textures[5]);
	possess_control(set_entity_tex(create_entity(&data, vec(26, 8), data.textures[6]), data.textures[7], data.textures[8], data.textures[9]), true);

	init_test(&data);

	mlx_loop(data.mlx);
	free_data(&data);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (0);
}
