/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:42:41 by fparis            #+#    #+#             */
/*   Updated: 2024/09/19 18:16:56 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_all_rays_old(t_data *data)
{
	int			i;
	float		rad_i;
	t_vectorf	direc;
	float		space;

	i = 0;
	space = (float)FOV / NB_RAYS;
	rad_i = data->player.angle - (space * (NB_RAYS / 2));
	if (rad_i < 0)
		rad_i += 2 * M_PI;
	while (i < NB_RAYS)
	{
		direc.x = cosf(rad_i);
		direc.y = sinf(rad_i);
		data->player.vision[i] = get_impact(data->player.pos, direc, data);
		data->player.vision[i].angle = rad_i;
		rad_i += space;
		if (rad_i > 2 * M_PI)
			rad_i -= 2 * M_PI;
		i++;
	}
}

void	get_all_rays(t_data *data)
{
	double		camera;
	int			i;
	//float		diff;
	t_vectorf	direc;

	i = 0;
	while (i < NB_RAYS)
	{
		camera = (2 * i / (double) NB_RAYS) - 1;
		direc.x = data->player.direction.x + data->player.camera_plane.x * camera;
		direc.y = data->player.direction.y + data->player.camera_plane.y * camera;
		data->player.vision[i] = get_impact(data->player.pos, direc, data);
		i++;
	}
}

float	fix_fisheye(t_data *data, t_impact ray, float size)
{
	float	p_angle;
	float	r_angle;
	float	c_angle;

	p_angle = data->player.angle;
	r_angle = ray.angle;
	c_angle = p_angle - r_angle;
	if (c_angle > 2 * M_PI)
		c_angle -= 2 * M_PI;
	if (c_angle < 0)
		c_angle += 2 * M_PI;
	size *= cosf(c_angle);
	return (size);
}

void	draw_ray(t_data *data, float diff, t_impact ray, int i)
{
	int			i2;
	int			size;
	int			color;
	t_vector	posy;

	if (ray.face == 0)
		return ;
	if (ray.length <= 0)
		size = 0;
	else
		size = (data->win_size.y / (ray.length / (data->scale * 2)));
	if (ray.face == 1 || ray.face == 3)
		color = 0xFF349CEB;
	else
		color = 0xFF3172A3;
	posy.x = (data->win_size.y - size) / 2;
	posy.y = (data->win_size.y + size) / 2;
	i2 = 0;
	while (i2 < diff)
	{
		draw_line_raycast(data, i * diff + i2, posy.x + data->player.pitch + (data->player.height / ray.length), posy.y + data->player.pitch + (data->player.height / ray.length), color);
		//draw_line(data, vec((i * diff) + i2, 0), vec((i * diff) + i2, posy.x), linfo(0xFF0000BB, 1, data->check_shape[0]));
		//draw_line(data, vec((i * diff) + i2, posy.x), vec((i * diff) + i2, posy.y), linfo(color, 1, data->check_shape[0]));
		//draw_line(data, vec((i * diff) + i2, posy.y), vec((i * diff) + i2, data->win_size.y), linfo(0xFF00BB00, 1, data->check_shape[0]));
		i2++;
	}
}

void	show_screen(t_data *data)
{
	int			i;
	float		diff;
	int			color;
	t_impact	*vision;

	if (!data->screen_display)
		data->screen_display = mlx_new_image(data->mlx, data->win_size.x, data->win_size.y);
	vision = data->player.vision;
	i = 0;
	diff = (float)data->win_size.x / (float)NB_RAYS;
	while (i < NB_RAYS)
	{
		draw_ray(data, diff, data->player.vision[i], i);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->screen_display, 0, 0);
}
