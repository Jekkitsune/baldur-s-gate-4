/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:44:42 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 20:26:39 by fparis           ###   ########.fr       */
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
		//printf("%d\n", fps);
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
	update_all_timer_properties(data, false);
	update_chunk(data);
	show_screen(data);
	party_refresh(data);
	update_data_time(data);
	return (0);
}

void	init_test(t_data *data)
{
	t_entity	*test2;

	add_prefab(data, get_prefab_data(data, "prefabs/guard"), ft_strjoin("guard", ""));
	data->prefab_tab[data->nb_prefab - 1]->sheet.hp = 10;
	data->prefab_tab[data->nb_prefab - 1]->sheet.max_hp = 10;
	data->prefab_tab[data->nb_prefab - 1]->sheet.type = living;
	data->prefab_tab[data->nb_prefab - 1]->sheet.description = ft_strdup("MOI QUAND LE LOUP EST ENSTEIN");
	test2 = spawn_entity(data, get_prefab(data, "guard"), vec(25, 10), ft_strjoin("john", ""));
	add_active(data, test2, NULL);

	add_prefab(data, get_prefab_data(data, "prefabs/omen"), ft_strjoin("omen", ""));
	add_prefab(data, get_prefab_data(data, "prefabs/wizard"), ft_strjoin("wizard", ""));

	test2 = spawn_entity(data, get_prefab(data, "omen"), vec(20, 3), ft_strjoin("omen", ""));
	test2->sheet.wander_ia = base_aggro;
	test2->sheet.team = 1;
	test2->sheet.fight_ia = martial_ia;
	add_active(data, test2, test2->sheet.wander_ia);
	test2->size_scale = 0.9; 

	test2 = spawn_entity(data, get_prefab(data, "omen"), vec(20, 2), ft_strjoin("omen", ""));
	test2->sheet.wander_ia = base_aggro;
	test2->sheet.team = 1;
	test2->sheet.fight_ia = martial_ia;
	add_active(data, test2, test2->sheet.wander_ia);
	test2->size_scale = 0.9; 

	test2 = spawn_entity(data, get_prefab(data, "omen"), vec(20, 4), ft_strjoin("omen", ""));
	test2->sheet.wander_ia = base_aggro;
	test2->sheet.team = 1;
	test2->sheet.fight_ia = martial_ia;
	add_active(data, test2, test2->sheet.wander_ia);
	test2->size_scale = 0.9; 

	test2 = spawn_entity(data, get_prefab(data, "wizard"), vec(26, 9), ft_strjoin("lisa", ""));
	add_active(data, test2, NULL);
	possess_control(test2, true);
	ft_lstadd_front(&data->round_manager.party, ft_lstnew(test2));
	test2->size_scale = 0.9;

	test2 = spawn_entity(data, get_prefab(data, "wizard"), vec(26, 9), ft_strjoin("lisa", ""));
	add_active(data, test2, NULL);
	possess_control(test2, true);
	ft_lstadd_front(&data->round_manager.party, ft_lstnew(test2));
	test2->size_scale = 0.9;

	test2 = spawn_entity(data, get_prefab(data, "wizard"), vec(26, 9), ft_strjoin("lisa", ""));
	add_active(data, test2, NULL);
	possess_control(test2, true);
	ft_lstadd_front(&data->round_manager.party, ft_lstnew(test2));
	test2->size_scale = 0.9;
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	if (!parsing(argc, argv, &data))
		exit_free(&data, "Parsing error");
	bool	e = true;
	for (int i = 0; i < data.current_map->size.x; i++)
	{
		for (int j = 0; j < data.current_map->size.y; j++)
		{
			if (data.current_map->arr[i][j].type == GROUND)
			{
				if (e)
				{
					data.current_map->arr[i][j].ceiling = false;
					e = false;
				}
				else
				{
					data.current_map->arr[i][j].ceiling = true;
					e = true;
				}
			}
		}
	}
	if (!check_textures(data.wall_tex))
		exit_free(&data, "Cannot create texture");
	init_player(&data);
	create_minimap(&data, 100, 20);
	mlx_set_fps_goal(data.mlx, FPS_CAP);
	init_mlx_events(&data);
	update_chunk(&data);
	mlx_loop_hook(data.mlx, loop, &data);
	init_textures(&data);
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
