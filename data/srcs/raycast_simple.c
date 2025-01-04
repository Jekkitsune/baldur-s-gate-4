/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:03:04 by fparis            #+#    #+#             */
/*   Updated: 2024/12/19 22:21:45 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_impact	*simple_check_wall(t_impact *impact, t_data *data, t_vectorf length, t_vectorf slope_coeff, t_vector sign)
{
	if (!in_bound(data->current_map, impact->wall_pos)
		|| ft_min(ft_absf(length.x), ft_absf(length.y)) > data->render_distance)
		return (impact);
	if (data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y].type != WALL
		&& data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y].type != DOOR)
		return (NULL);
	impact->cell = &data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y];
	if (ft_absf(length.x) <= ft_absf(length.y))
	{
		impact->face = 2;
		if (length.x < 0)
			impact->face = 4;
		impact->length = ft_absf(length.x);
	}
	else
	{
		impact->face = 1;
		if (length.y < 0)
			impact->face = 3;
		impact->length = ft_absf(length.y);
	}
	return (impact);
}

t_impact	simple_raycast(t_vector start, t_vectorf direc, t_data *data, t_vectorf slope_coef)
{
	t_vector	sign;
	t_vectorf	length;
	t_impact	impact;

	impact.face = 0;
	impact.length = 0;
	impact.direc.x = direc.x;
	impact.direc.y = direc.y;
	if (direc.x < 0)
	{
		sign.x = -1;
		length.x = (float)((data->player.offset.x + data->scale) / (float)(data->scale * 2)) * slope_coef.x * sign.x;
	}
	else
	{
		sign.x = 1;
		length.x = ((float)(1 - ((float)(data->player.offset.x + data->scale)) / (float)(data->scale * 2))) * slope_coef.x;
	}
	if (direc.y < 0)
	{
		sign.y = -1;
		length.y = (float)((data->player.offset.y + data->scale) / (float)(data->scale * 2)) * slope_coef.y * sign.y;
	}
	else
	{
		sign.y = 1;
		length.y = ((float)(1 - ((float)(data->player.offset.y + data->scale)) / (float)(data->scale * 2))) * slope_coef.y;
	}
	slope_coef.x *= sign.x;
	slope_coef.y *= sign.y;
	impact.wall_pos.x = start.x;
	impact.wall_pos.y = start.y;
	while (ft_absf(length.x) < data->render_distance || ft_absf(length.y) < data->render_distance)
	{
		while (ft_absf(length.x) <= ft_absf(length.y))
		{
			impact.wall_pos.x += sign.x;
			if (simple_check_wall(&impact, data, length, slope_coef, sign))
				return (impact);
			length.x += slope_coef.x;
		}
		while (ft_absf(length.y) <= ft_absf(length.x))
		{
			impact.wall_pos.y += sign.y;
			if (simple_check_wall(&impact, data, length, slope_coef, sign))
				return (impact);
			length.y += slope_coef.y;
		}
	}
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
