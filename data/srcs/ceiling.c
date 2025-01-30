/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:42:41 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 05:50:27 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_skybox2(t_data *data, t_ceiling c, t_skybox s, t_vector it)
{
	if (it.x >= s.left_seg.x && it.x <= s.left_seg.y)
	{
		s.pixel_length = ft_abs(s.left_seg.y - s.left_seg.x);
		c.pli = (s.pixel_length * s.left_tex->size) / data->win_size.x;
		c.st = s.left_tex->size - c.pli - 1;
		c.t.x = it.x * (s.left_tex->size - 1) / (data->win_size.x - 1) + c.st;
		if (c.t.x >= s.left_tex->size)
			c.t.x = s.left_tex->size - 1;
		c.t.y = ((it.y * (s.left_tex->size - 1)) / (data->win_size.y - 1));
		c.color = s.left_tex->tab[c.t.x][c.t.y];
	}
	else if (it.x >= s.right_seg.x && it.x <= s.right_seg.y)
	{
		s.pixel_length = ft_abs(s.right_seg.y - s.right_seg.x);
		c.pli = (s.pixel_length * s.right_tex->size) / data->win_size.x;
		c.st = s.right_tex->size - c.pli - 1;
		c.t.x = it.x * (s.right_tex->size - 1) / (data->win_size.x - 1) - c.st;
		c.t.y = ((it.y * (s.right_tex->size - 1)) / (data->win_size.y - 1));
		if (c.t.x < 0)
			c.t.x = 0;
		c.color = s.right_tex->tab[c.t.x][c.t.y];
	}
	if (data->win_size.y - it.y - 1 < c.lim)
		data->screen_buffer[data->win_size.y - it.y - 1][it.x] = c.color;
}

void	handle_skybox(t_data *data, t_ceiling c, int x, int y)
{
	t_skybox	s;
	bool		ceiling;

	s = *c.s;
	ceiling = c.cell.x >= 0 && c.cell.y >= 0
		&& c.cell.x < data->current_map->size.x
		&& c.cell.y < data->current_map->size.y
		&& data->current_map->arr[c.cell.x][c.cell.y].ceiling;
	if (!ceiling)
		handle_skybox2(data, c, s, vec(x, y));
	else
	{
		c.color = data->ceiling->tab[c.t.x][c.t.y];
		if (data->win_size.y - y - 1 < c.lim)
			data->screen_buffer[data->win_size.y - y - 1][x] = c.color;
	}
}

void	calculate_ceiling(t_data *data, t_ceiling c, int y)
{
	int	x;

	x = -1;
	while (++x < data->win_size.x)
	{
		c.cell.x = (int) c.floor.x;
		c.cell.y = (int) c.floor.y;
		c.t.y = ((int)(data->ceiling->size * (c.floor.y - c.cell.y)) % \
			(data->ceiling->size - 1));
		c.t.x = ((int)(data->ceiling->size * (c.floor.x - c.cell.x)) % \
			(data->ceiling->size - 1));
		if (c.t.x < 0)
			c.t.x = 0;
		if (c.t.y < 0)
			c.t.y = 0;
		c.floor.x += c.floor_step.x;
		c.floor.y += c.floor_step.y;
		handle_skybox(data, c, x, y);
	}
}

void	show_ceiling2(t_data *data, t_ceiling *c, int y)
{
	int	p;

	c->ray_dir_0.x = data->player.direction.x - data->player.camera_plane.x;
	c->ray_dir_0.y = data->player.direction.y - data->player.camera_plane.y;
	c->ray_dir_1.x = data->player.direction.x + data->player.camera_plane.x;
	c->ray_dir_1.y = data->player.direction.y + data->player.camera_plane.y;
	p = y - c->horizon;
	c->cam_z = ((data->player.height * (data->win_size.y / 2)) / HEIGHT_CAP);
	c->cam_z = (data->win_size.y / 2) - ((c->cam_z * HEIGHT_CAP / \
		(data->scale * 2)) / (data->win_size.y / 2));
	c->row_distance = c->cam_z / p;
	c->floor_step.x = c->row_distance * (c->ray_dir_1.x - c->ray_dir_0.x) \
		/ data->win_size.x;
	c->floor_step.y = c->row_distance * (c->ray_dir_1.y - c->ray_dir_0.y) \
		/ data->win_size.x;
	c->floor.x = (data->player.pos.x + (5 + data->player.offset.x / 2) / 10) \
		+ c->row_distance * c->ray_dir_0.x;
	c->floor.y = (data->player.pos.y + (5 + data->player.offset.y / 2) / 10) \
		+ c->row_distance * c->ray_dir_0.y;
}

void	show_ceiling(t_data *data)
{
	int			y;
	t_ceiling	c;
	t_skybox	s;

	c.s = &s;
	skybox(data, c.s);
	c.horizon = (data->win_size.y / 2) - data->player.pitch;
	c.lim = (data->win_size.y / 2) + data->player.pitch;
	y = -1;
	while (++y < data->win_size.y)
	{
		show_ceiling2(data, &c, y);
		calculate_ceiling(data, c, y);
	}
}
