/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:55:21 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/29 13:55:23 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_impact	*check_wall(t_impact *impact, t_data *data, t_vectorf length)
{
	if (!in_bound(data->map, impact->wall_pos)
		|| ft_min(ft_absf(length.x), ft_absf(length.y)) > data->render_distance)
		return (impact);
	if (!length.x || !length.y)
		return (NULL);
	if (data->map->arr[impact->wall_pos.x][impact->wall_pos.y].type
		!= WALL)
		return (NULL);
	impact->cell
		= &data->map->arr[impact->wall_pos.x][impact->wall_pos.y];
	return (found_wall(impact, length));
}

t_vectorf	starting_length(t_data *data, t_vectorf direc, t_vector *sign,
	t_impact *impact)
{
	t_vectorf	length;

	sign->x = -1;
	if (direc.x < 0)
		length.x = (float)((data->player.offset.x + data->scale)
				/ (float)(data->scale * 2)) *impact->slope_coef.x * sign->x;
	else
	{
		sign->x = 1;
		length.x = ((float)(1 - ((float)(data->player.offset.x + data->scale))
					/ (float)(data->scale * 2))) * impact->slope_coef.x;
	}
	sign->y = -1;
	if (direc.y < 0)
		length.y = (float)((data->player.offset.y + data->scale)
				/ (float)(data->scale * 2)) *impact->slope_coef.y * sign->y;
	else
	{
		sign->y = 1;
		length.y = ((float)(1 - ((float)(data->player.offset.y + data->scale))
					/ (float)(data->scale * 2))) * impact->slope_coef.y;
	}
	return (length);
}

t_bool	raycast_loop(t_data *data, t_impact *impact, t_vectorf length,
	t_vector sign)
{
	while (ft_absf(length.x) < data->render_distance
		|| ft_absf(length.y) < data->render_distance)
	{
		while (ft_absf(length.x) <= ft_absf(length.y))
		{
			impact->wall_pos.x += sign.x;
			if (check_wall(impact, data, length))
				return (true);
			length.x += impact->slope_coef.x;
		}
		while (ft_absf(length.y) <= ft_absf(length.x))
		{
			impact->wall_pos.y += sign.y;
			if (check_wall(impact, data, length))
				return (true);
			length.y += impact->slope_coef.y;
		}
	}
	return (false);
}

t_impact	raycast(t_vector start, t_vectorf direc, t_data *data,
	t_vectorf slope_coef)
{
	t_vector	sign;
	t_vectorf	length;
	t_impact	impact;

	impact.face = 0;
	impact.length = 0;
	impact.direc.x = direc.x;
	impact.direc.y = direc.y;
	impact.slope_coef.x = slope_coef.x;
	impact.slope_coef.y = slope_coef.y;
	length = starting_length(data, direc, &sign, &impact);
	impact.slope_coef.x *= sign.x;
	impact.slope_coef.y *= sign.y;
	impact.wall_pos.x = start.x;
	impact.wall_pos.y = start.y;
	if (raycast_loop(data, &impact, length, sign))
		return (impact);
	impact.face = 0;
	impact.length = data->render_distance;
	return (impact);
}

t_impact	get_impact(t_vector start, t_vectorf direc, t_data *data)
{
	t_vectorf	delta;
	t_vectorf	slope_coef;

	delta.x = ft_absf(direc.x * 100);
	delta.y = ft_absf(direc.y * 100);
	slope_coef.x = data->scale * 2;
	slope_coef.y = data->scale * 2;
	if (delta.x != 0)
		slope_coef.x = fabs((double)(data->scale * 2) / direc.x);
	if (delta.y != 0)
		slope_coef.y = fabs((double)(data->scale * 2) / direc.y);
	return (raycast(start, direc, data, slope_coef));
}
