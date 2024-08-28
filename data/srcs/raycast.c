/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:33:20 by fparis            #+#    #+#             */
/*   Updated: 2024/08/28 19:42:24 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_impact	*check_wall(t_impact *impact, t_data *data, t_vectorf length, t_vector impact_pos)
{
	if (!in_bound(*data->current_map, impact->wall_pos)
		|| ft_min(ft_absf(length.x), ft_absf(length.y)) > data->render_distance)
	{
		impact->face = 0;
		return (impact);
	}
	if (data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y] != WALL)
		return (NULL);
	impact->impact_pos = impact_pos;
	if (ft_absf(length.x) <= ft_absf(length.y))
	{
		impact->face = 2;
		if (length.x < 0)
			impact->face = 4;
		impact->length = ft_absf(length.x);
		return (impact);
	}
	else
	{
		impact->face = 1;
		if (length.y < 0)
			impact->face = 3;
		impact->length = ft_absf(length.y);
		return (impact);
	}
}

t_impact	raycast(t_vector start, t_vectorf direc, t_data *data, t_vectorf slope_coef)
{
	t_vector	sign;
	t_vectorf	length;
	t_impact	impact;

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
			if (check_wall(&impact, data, length, vec(start.x + (direc.x * length.x), start.y + (direc.y * length.x))))
				return (impact);
			length.x += slope_coef.x;
		}
		while (ft_absf(length.y) <= ft_absf(length.x))
		{
			impact.wall_pos.y += sign.y;
			if (check_wall(&impact, data, length, vec(start.x + (direc.x * length.y), start.y + (direc.y * length.y))))
				return (impact);
			length.y += slope_coef.y;
		}
	}
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
		slope_coef.x = sqrt(pow(data->scale * 2, 2) + pow(delta.y / delta.x * (data->scale * 2), 2));
	if (delta.y != 0)
		slope_coef.y = sqrt(pow(data->scale * 2, 2) + pow(delta.x / delta.y * (data->scale * 2), 2));
	return (raycast(start, direc, data, slope_coef));
}
