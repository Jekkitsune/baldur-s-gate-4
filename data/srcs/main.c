/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:44:42 by fparis            #+#    #+#             */
/*   Updated: 2025/01/27 03:37:16 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_data_time(t_data *data)
{
	struct timeval	new_time;

	gettimeofday(&new_time, NULL);
	data->frame_time = ((new_time.tv_sec - data->current_time.tv_sec)
		* 1000000) + new_time.tv_usec - data->current_time.tv_usec;
	static int fps = 0;
	static unsigned long count = 0;
	if (new_time.tv_sec != data->current_time.tv_sec)
	{
		data->player.speed = (double) 1 / ((double)fps / (double) FPS_CAP);
		count = 0;
		fps = 0;
	}
	if (data->player.speed > 30)
		data->player.speed = 0;
	fps++;
	count += data->frame_time;
	data->current_time = new_time;
}

int	loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	camera_move(data);
	if (data->player.focus_mode)
		rotate_focus(data);
	move(data);
	update_doors(data);
	update_all_active(data);
	update_all_timer_effects(data, false);
	update_chunk(data);
	show_screen(data);
	update_data_time(data);
	return (0);
}

void	init_test(t_data *data)
{
	t_entity	*test2;

	test2 = spawn_entity(data, get_prefab(data, "wizard"), vec(26, 9), ft_strjoin("lisa", ""));
	add_active(data, test2, NULL);
	possess_control(test2, true);
	if (test2)
		ft_lstadd_front(&data->round_manager.party, ft_lstnew(test2));

	test2 = spawn_entity(data, get_prefab(data, "wizard"), vec(26, 9), ft_strjoin("lisa", ""));
	add_active(data, test2, NULL);
	possess_control(test2, true);
	if (test2)
		ft_lstadd_front(&data->round_manager.party, ft_lstnew(test2));

	test2 = spawn_entity(data, get_prefab(data, "wizard"), vec(26, 9), ft_strjoin("lisa", ""));
	add_active(data, test2, NULL);
	possess_control(test2, true);
	if (test2)
		ft_lstadd_front(&data->round_manager.party, ft_lstnew(test2));
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	if (!parsing(argc, argv, &data))
		exit_free(&data, "Parsing error");
	if (!check_textures(data.wall_tex))
		exit_free(&data, "Cannot create texture");

	init_game(&data);

	init_test(&data);
	if (data.round_manager.party)
		possess(&data, data.round_manager.party->content);
	init_mlx_events(&data);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);
	free_data(&data);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	return (0);
}
