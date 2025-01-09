/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:36:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/08 17:23:09 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_down(t_data *data, int key)
{
	if ((data->player.focus_mode && key == 3))
	{
		mlx_mouse_get_pos(data->mlx, &data->player.mouse_pos.x, &data->player.mouse_pos.y);
		mlx_mouse_hide();
		mlx_mouse_move(data->mlx, data->win, data->win_size.x / 2, data->win_size.y / 2);
	}
	else if (!data->player.focus_mode && key == 3)
	{
		mlx_mouse_move(data->mlx, data->win, data->player.mouse_pos.x, data->player.mouse_pos.y);
		mlx_mouse_show();
	}
}

void	mouse_up(t_data *data, int key)
{
	if ((data->player.focus_mode && key == 3))
	{
		mlx_mouse_move(data->mlx, data->win, data->player.mouse_pos.x, data->player.mouse_pos.y);
		mlx_mouse_show();
	}
	if (!data->player.focus_mode && key == 3)
	{
		mlx_mouse_get_pos(data->mlx, &data->player.mouse_pos.x, &data->player.mouse_pos.y);
		mlx_mouse_hide();
		mlx_mouse_move(data->mlx, data->win, data->win_size.x / 2, data->win_size.y / 2);
	}
}

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

	if (data->player.mouse_wheel)
	{
		if (data->player.focus_mode)
		{
			if (data->player.mouse_wheel == 1 && data->player.focus_dist > 15)
				data->player.focus_dist -= data->player.speed * 5;
			if (data->player.mouse_wheel == 2 && data->player.focus_dist < 100)
				data->player.focus_dist += data->player.speed * 5;
		}
		data->player.mouse_wheel = 0;
	}
	if ((data->player.focus_mode && !data->player.mouse_button[2]) || (!data->player.focus_mode && data->player.mouse_button[2]))
		return ;
	mlx_mouse_get_pos(data->mlx, &mouse_pos.x, &mouse_pos.y);
	if (mouse_pos.x == data->player.mouse_pos.x && mouse_pos.y == data->player.mouse_pos.y)
		return ;
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
			if ((mouse_pos.y < 0 && data->player.height < HEIGHT_CAP) || (mouse_pos.y > 0 && data->player.height > -HEIGHT_CAP))
			{
				
				data->player.height -= mouse_pos.y * 10;
			}
			if ((mouse_pos.y < 0 && data->player.pitch > -75) || (mouse_pos.y > 0 && data->player.pitch < 75))
				data->player.pitch += mouse_pos.y / 8;
		}
		else
			data->player.pitch += mouse_pos.y;
	}
	if (data->on_screen)
		mlx_mouse_move(data->mlx, data->win, data->win_size.x / 2, data->win_size.y / 2);
}
