/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:44:42 by fparis            #+#    #+#             */
/*   Updated: 2024/12/13 18:19:50 by fparis           ###   ########.fr       */
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
			remove_selector(data);
		}
	}

	move(data);
	update_all_active(data);
	//update_button_action(data);
	update_chunk(data);
	show_screen(data);

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
	if (!check_textures(data.wall_tex))
		exit_free(&data, "Cannot create texture");

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

	add_tex(&data, path_to_tex(&data, "hutao.png"), ft_strdup("test"));
	add_tex(&data, path_to_tex(&data, "postal.png"), NULL);
	add_tex(&data, path_to_tex(&data, "s1.png"), ft_strdup("skybox1"));
	add_tex(&data, path_to_tex(&data, "s2.png"), ft_strdup("skybox2"));
	add_tex(&data, path_to_tex(&data, "s3.png"), ft_strdup("skybox3"));
	add_tex(&data, path_to_tex(&data, "s4.png"), ft_strdup("skybox4"));
	data.sky_box_tex[0] = get_tex(&data, "skybox1");
	data.sky_box_tex[1] = get_tex(&data, "skybox2");
	data.sky_box_tex[2] = get_tex(&data, "skybox3");
	data.sky_box_tex[3] = get_tex(&data, "skybox4");
	add_tex(&data, path_to_tex(&data, "brickwall.png"), ft_strdup("ceiling"));
	add_tex(&data, path_to_tex(&data, "woodwall.png"), ft_strdup("floor"));
	data.ceiling = get_tex(&data, "ceiling");
	data.floor = get_tex(&data, "floor");
	add_tex(&data, get_resized_button(&data, path_to_tex(&data, "fireball_button.png")), ft_strdup("fireball_button"));
	add_tex(&data, get_resized_button(&data, path_to_tex(&data, "take_button.png")), ft_strdup("take_button"));
	add_tex(&data, get_resized_button(&data, path_to_tex(&data, "inventory_button.png")), ft_strdup("inventory_button"));

	init_test(&data);
	load_spells_prefab(&data);

	mlx_loop(data.mlx);
	free_data(&data);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (0);
}
