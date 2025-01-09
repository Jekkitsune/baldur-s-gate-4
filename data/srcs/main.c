/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:44:42 by fparis            #+#    #+#             */
/*   Updated: 2025/01/09 12:30:10 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop(void *param)
{
	t_data 			*data;
	struct timeval 	new_time;

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
		if (in_bound(data->current_map, data->player.pos) && data->current_map->arr[data->player.pos.x][data->player.pos.y].entities)
			entitest = data->current_map->arr[data->player.pos.x][data->player.pos.y].entities->content;
		if (!data->player.focus_mode && entitest)
			possess(data, entitest);
		else if (data->player.focus_mode)
		{
			unpossess(data);
			remove_selector(data, false);
		}
		else if (data->current_map->active_entities && data->current_map->active_entities->content)
		{
			t_entity *owo = data->current_map->active_entities->content;
			move_to(data, owo, data->player.pos);
		}
	}

	//printf("%p\n", data->player.active_button);

	move(data);
	update_doors(data);
	update_all_active(data);
	update_all_timer_effects(data, false);
	update_all_timer_properties(data, false);
	update_chunk(data);
	show_screen(data);

	party_refresh(data);

	gettimeofday(&new_time, NULL);
	data->frame_time = ((new_time.tv_sec - data->current_time.tv_sec)
		* 1000000) + new_time.tv_usec - data->current_time.tv_usec;
	
	static int fps = 0;
	static unsigned long count = 0;
	//if (count > 1000000)
	if (new_time.tv_sec != data->current_time.tv_sec)
	{
		data->player.speed = (double) 1 / ((double)fps / (double) FPS_CAP);
		//printf("%d\n", fps);
		count = 0;
		fps = 0;
	}
	if (data->player.speed > 30)
		data->player.speed = 0;
	fps++;
	count += data->frame_time;
	data->current_time = new_time;

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

	create_minimap(&data, 100, 20);

	mlx_set_fps_goal(data.mlx, FPS_CAP);
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
	add_tex(&data, get_resized_free(&data, path_to_tex(&data, "fireball_button.png"), data.button_scale_size), ft_strdup("fireball_button"));
	add_tex(&data, get_resized_free(&data, path_to_tex(&data, "take_button.png"), data.button_scale_size), ft_strdup("take_button"));
	add_tex(&data, get_resized_free(&data, path_to_tex(&data, "inventory_button.png"), data.button_scale_size), ft_strdup("inventory_button"));
	add_tex(&data, get_resized_free(&data, path_to_tex(&data, "check_button.png"), data.button_scale_size), ft_strdup("check_button"));
	add_tex(&data, get_resized_free(&data, path_to_tex(&data, "move_button.png"), data.button_scale_size), ft_strdup("move_button"));
	add_tex(&data, get_resized_free(&data, path_to_tex(&data, "melee_button.png"), data.button_scale_size), ft_strdup("melee_button"));
	add_tex(&data, get_resized_free(&data, path_to_tex(&data, "range_button.png"), data.button_scale_size), ft_strdup("range_button"));
	add_tex(&data, get_resized_free(&data, path_to_tex(&data, "punch_button.png"), data.button_scale_size), ft_strdup("punch_button"));

	load_spells_prefab(&data);
	init_all_classes(&data);
	init_test(&data);

	if (data.round_manager.party)
		possess(&data, data.round_manager.party->content);

	mlx_loop(data.mlx);
	free_data(&data);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (0);
}
