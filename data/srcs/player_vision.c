/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:42:41 by fparis            #+#    #+#             */
/*   Updated: 2024/08/28 21:29:48 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_all_rays(t_data *data)
{
	int			i;
	float		rad_i;
	t_vectorf	direc;
	float		space;

	i = 0;
	space = FOV / NB_RAYS;
	rad_i = data->player.angle - (space * (NB_RAYS / 2));
	if (rad_i < 0)
		rad_i += 2 * M_PI;
	while (i < NB_RAYS)
	{
		direc.x = cosf(rad_i);
		direc.y = sinf(rad_i);
		data->player.vision[i] = get_impact(data->player.pos, direc, data);
		rad_i += space;
		if (rad_i > 2 * M_PI)
			rad_i -= 2 * M_PI;
		i++;
	}
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
		size = data->render_distance * (data->win_size.y / data->render_distance);
	else
		size = (data->render_distance / ray.length) * (data->win_size.y / data->render_distance);
	//size += 10;
	size *= 10;
	if (ray.face == 1 || ray.face == 3)
		color = 0xFF349CEB;
	else
		color = 0xFF3172A3;
	posy.x = (data->win_size.y - size) / 2;
	posy.y = (data->win_size.y + size) / 2;
	i2 = 0;
	while (i2 < diff)
	{
		draw_line(data, vec((i * diff) + i2, posy.x), vec((i * diff) + i2, posy.y), vec(color, 1));
		i2++;
	}
}

void	show_screen(t_data *data)
{
	int			i;
	float		diff;
	int			color;
	t_impact	*vision;

	vision = data->player.vision;
	i = 0;
	diff = data->win_size.x / NB_RAYS;
	while (i < NB_RAYS)
	{
		draw_ray(data, diff, data->player.vision[i], i);
		i++;
	}
}
