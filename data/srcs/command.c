/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:29:09 by fparis            #+#    #+#             */
/*   Updated: 2024/11/22 19:24:16 by fparis           ###   ########.fr       */
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
	if (key == 44)
	{
		int	i = 0;
		while (i < data->current_map->size.x)
		{
			int	j = 0;
			while (j < data->current_map->size.y)
			{
				if (data->current_map->arr[i][j].type == DOOR)
				{
					if (data->current_map->arr[i][j].status == OPEN)
						data->current_map->arr[i][j].status = CLOSE;
					else if (data->current_map->arr[i][j].status == CLOSE)
						data->current_map->arr[i][j].status = OPEN;
				}
				j++;
			}
			i++;
		}
	}
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
		data->player.is_running = 1;
	if (key == 8)
		data->test_key = 1;
	if (key == 6)
		data->sky_box = !data->sky_box;
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
		data->player.is_running = 0;
	return (0);
}

int	mouse_down_manager(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key >= 1 && key < 4)
		data->player.mouse_button[key - 1] = 1;
	if (key == 3)
	{
		mlx_mouse_get_pos(data->mlx, &data->player.mouse_pos.x, &data->player.mouse_pos.y);
		mlx_mouse_hide();
		mlx_mouse_move(data->mlx, data->win, data->win_size.x / 2, data->win_size.y / 2);
	}
	return (0);
}

int	mouse_up_manager(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key >= 1 && key < 4)
		data->player.mouse_button[key - 1] = 0;
	if (data->player.focus_mode && key == 3)
	{
		mlx_mouse_move(data->mlx, data->win, data->player.mouse_pos.x, data->player.mouse_pos.y);
		mlx_mouse_show();
	}
	if (key == 1 || key == 3)
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
