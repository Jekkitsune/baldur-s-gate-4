/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:42:41 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:35:42 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_floor(t_data *data, t_floor *f, int y)
{
	int			x;
	uint32_t	color;
	t_texture	*tex;

	x = -1;
	while (++x < data->win_size.x)
	{
		f->cell.x = (int) f->floor.x;
		f->cell.y = (int) f->floor.y;
		tex = data->current_map->floor;
		if (in_bound(data->current_map, f->cell)
			&& data->current_map->arr[f->cell.x][f->cell.y].floor_tex)
			tex = data->current_map->arr[f->cell.x][f->cell.y].floor_tex;
		f->t.y = ((int)(tex->size * (f->floor.y - f->cell.y)) \
			% (tex->size - 1));
		f->t.x = ((int)(tex->size * (f->floor.x - f->cell.x)) \
			% (tex->size - 1));
		f->t.x = ft_max(f->t.x, 0);
		f->t.y = ft_max(f->t.y, 0);
		f->floor.x += f->floor_step.x;
		f->floor.y += f->floor_step.y;
		color = tex->tab[f->t.x][f->t.y];
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
		y = -1;
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
