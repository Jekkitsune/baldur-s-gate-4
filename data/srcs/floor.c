/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:42:41 by fparis            #+#    #+#             */
/*   Updated: 2025/01/17 02:03:29 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_floor(t_data *data, t_floor *f, int y)
{
	int			x;
	uint32_t	color;

	x = -1;
	while (++x < data->win_size.x)
	{
		f->cell.x = (int) f->floor.x;
		f->cell.y = (int) f->floor.y;
		f->t.y = ((int) (data->floor->size * (f->floor.y - f->cell.y))\
			% (data->floor->size - 1));
		f->t.x = ((int) (data->floor->size * (f->floor.x - f->cell.x))\
			% (data->floor->size - 1));
		if (f->t.x < 0)
			f->t.x = 0;
		if (f->t.y < 0)
			f->t.y = 0;
		f->floor.x += f->floor_step.x;
		f->floor.y += f->floor_step.y;
		color = data->floor->tab[f->t.x][f->t.y];
		data->screen_buffer[y][x] = color;
	}
}

void	get_coords(t_data *data, t_floor *f)
{
	f->floor_step.x = f->row_distance * (f->ray_dir_1.x - f->ray_dir_0.x) \
		/ data->win_size.x;
	f->floor_step.y = f->row_distance * (f->ray_dir_1.y - f->ray_dir_0.y) \
		/ data->win_size.x;
	f->floor.x = (data->player.pos.x + (5 + data->player.offset.x / 2) \
		/ 10) + f->row_distance * f->ray_dir_0.x;
	f->floor.y = (data->player.pos.y + (5 + data->player.offset.y / 2) \
		/ 10) + f->row_distance * f->ray_dir_0.y;
}

void	show_floor(t_data *data)
{
	int			y;
	int			p;
	t_floor		f;

	f.horizon = (data->win_size.y / 2) + data->player.pitch;
	y = f.horizon - 1;
	if (y < 0)
		y = - 1;
	while (++y < data->win_size.y)
	{
		f.ray_dir_0.x = data->player.direction.x - data->player.camera_plane.x;
		f.ray_dir_0.y = data->player.direction.y - data->player.camera_plane.y;
		f.ray_dir_1.x = data->player.direction.x + data->player.camera_plane.x;
		f.ray_dir_1.y = data->player.direction.y + data->player.camera_plane.y;
		p = y - f.horizon;
		f.cam_z = ((data->player.height * (data->win_size.y / 2)) / HEIGHT_CAP);
		f.cam_z = (data->win_size.y / 2) + ((f.cam_z * HEIGHT_CAP / \
			(data->scale * 2)) / (data->win_size.y / 2));
		f.row_distance = f.cam_z / p;
		get_coords(data, &f);
		calculate_floor(data, &f, y);
	}
}
