/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:36:04 by fparis            #+#    #+#             */
/*   Updated: 2024/09/13 23:23:28 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_manager(int event, void *param)
{
	t_data	*data;

	data = param;
	//printf("event: %d\n", event);
	if (event == 7)
		data->on_screen = 0;
	if (event == 5)
		data->on_screen = 1;
	return (1);
}

void	camera_move(t_data *data)
{
	t_vector	mouse_pos;

	mlx_mouse_get_pos(data->mlx, &mouse_pos.x, &mouse_pos.y);
	if (mouse_pos.x != data->win_size.x / 2)
	{
		mouse_pos.x = (data->win_size.x / 2) - mouse_pos.x;
		data->player.angle = angle_add(data->player.angle, -(float)mouse_pos.x / 1000 * 1.2);
	}
	if (mouse_pos.y != data->win_size.y / 2)
	{
		mouse_pos.y = (data->win_size.y / 2) - mouse_pos.y;
		if (data->player.focus_mode)
		{
			if ((mouse_pos.y > 0 && data->player.height < 10000) || (mouse_pos.y < 0 && data->player.height > -5000))
			{
				data->player.pitch -= mouse_pos.y / 8;
				data->player.height += mouse_pos.y * 10;
			}
		}
		else
			data->player.pitch += mouse_pos.y;
	}
}
