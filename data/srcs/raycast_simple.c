/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:03:04 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 19:16:21 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vectorf	starting_length(t_data *data, t_vectorf direc, t_vector *sign,
				t_impact *impact);

t_impact	*simple_check_wall(t_impact *impact, t_data *data, t_vectorf length)
{
	if (!in_bound(data->current_map, impact->wall_pos)
		|| ft_min(ft_absf(length.x), ft_absf(length.y)) > data->render_distance)
		return (impact);
	if (data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y].type
		!= WALL
		&& data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y].type
		!= DOOR)
		return (NULL);
	impact->cell
		= &data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y];
	return (found_wall(impact, length));
}

t_bool	simple_ray_loop(t_data *data, t_impact *impact, t_vectorf length,
	t_vector sign)
{
	while (ft_absf(length.x) < data->render_distance
		|| ft_absf(length.y) < data->render_distance)
	{
		while (ft_absf(length.x) <= ft_absf(length.y))
		{
			impact->wall_pos.x += sign.x;
			if (simple_check_wall(impact, data, length))
				return (true);
			length.x += impact->slope_coef.x;
		}
		while (ft_absf(length.y) <= ft_absf(length.x))
		{
			impact->wall_pos.y += sign.y;
			if (simple_check_wall(impact, data, length))
				return (true);
			length.y += impact->slope_coef.y;
		}
	}
	return (false);
}

t_impact	simple_raycast(t_vector start, t_vectorf direc, t_data *data,
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
	slope_coef.x *= sign.x;
	slope_coef.y *= sign.y;
	impact.wall_pos.x = start.x;
	impact.wall_pos.y = start.y;
	if (simple_ray_loop(data, &impact, length, sign))
		return (impact);
	impact.face = 0;
	impact.length = data->render_distance;
	return (impact);
}

t_impact	get_simple_impact(t_vector start, t_vectorf direc, t_data *data)
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
	return (simple_raycast(start, direc, data, slope_coef));
}
