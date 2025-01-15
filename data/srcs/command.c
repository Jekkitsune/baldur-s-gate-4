/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:29:09 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 02:20:23 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	register_player_movement(t_data *data, int key, int pressed)
{
	if (key == 26)
		data->player.movement[0] = pressed;
	if (key == 4)
		data->player.movement[1] = pressed;
	if (key == 22)
		data->player.movement[2] = pressed;
	if (key == 7)
		data->player.movement[3] = pressed;
	if (key == 80)
		data->player.rotation[1] = pressed;
	if (key == 79)
		data->player.rotation[3] = pressed;
	if (key == 82)
		data->player.rotation[0] = pressed;
	if (key == 81)
		data->player.rotation[2] = pressed;
	if (key == 89)
		data->player.movement[4] = pressed;
	if (key == 90)
		data->player.movement[5] = pressed;
}

int	key_down_manager(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == 41)
		mlx_loop_end(data->mlx);
	if (key == 26 || key == 4 || key == 22 || key == 7 || (key >= 79 && key <= 82) || (key >= 89 && key <= 90))
		register_player_movement(data, key, 1);
	if (key == 225)
		data->player.description_mode = 1;
	if (key == 8)
		data->test_key = 1;
	if (key == 6 && data->sky_box_tex[0] && data->sky_box_tex[1]
		&& data->sky_box_tex[2] && data->sky_box_tex[3])
		data->sky_box = !data->sky_box;
	if (key == 44)
	{
		open_door(data);
		// if (in_bound(data->current_map, data->player.pos))
		// 	data->current_map->arr[data->player.pos.x][data->player.pos.y].fog_color = 0xAA13e80c;
	}
	return (0);
}

int	key_up_manager(int key, void *param)
{
	t_data	*data;

	//printf("key: %d\n", key);
	data = (t_data *)param;
	if (key == 26 || key == 4 || key == 22 || key == 7 || (key >= 79 && key <= 82) || (key >= 89 && key <= 90))
		register_player_movement(data, key, 0);
	if (key == 225)
		data->player.description_mode = 0;
	if (key == 29)
		cycle_entity_cell(data, -1);
	else if (key == 27)
		cycle_entity_cell(data, +1);
	return (0);
}

int	mouse_down_manager(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key >= 1 && key < 4)
		data->player.mouse_button[key - 1] = 1;
	mouse_down(data, key);
	return (0);
}

int	mouse_up_manager(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key >= 1 && key < 4)
		data->player.mouse_button[key - 1] = 0;
	mouse_up(data, key);
	if (key == 1)
		check_button_click(data);
	return (0);
}

int	mouse_wheel_manager(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->player.mouse_wheel = key;
	return (0);
}
