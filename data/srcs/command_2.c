/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:11:38 by fparis            #+#    #+#             */
/*   Updated: 2025/01/24 11:10:21 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	window_manager(int event, void *param)
{
	t_data	*data;

	data = param;
	if (event == 0)
		mlx_loop_end(data->mlx);
	if (event == 7)
		data->on_screen = 0;
	if (event == 5)
		data->on_screen = 1;
	return (1);
}
