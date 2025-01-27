/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:06:13 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 12:50:31 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_fog(t_impact *impact, t_data *data, t_vectorf length)
{
	t_cell	*cell;
	float	fog_length;

	cell = &data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y];
	if (!impact->has_fog && cell->fog_color)
	{
		impact->has_fog = true;
		if (ft_absf(length.x) <= ft_absf(length.y))
			fog_length = ft_absf(length.x);
		else
			fog_length = ft_absf(length.y);
		sort_fog(data, impact, fog_length);
	}
}

void	check_upper_wall(t_impact *impact, t_data *data, t_vectorf length)
{
	t_cell	*cell;

	cell = &data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y];
	if (!impact->upper_wall_cell && cell->upper_wall)
	{
		impact->upper_wall_cell = cell;
		if (ft_absf(length.x) <= ft_absf(length.y))
		{
			impact->upper_wall_face = 2;
			if (length.x < 0)
				impact->upper_wall_face = 4;
			impact->upper_wall_length = ft_absf(length.x);
		}
		else
		{
			impact->upper_wall_face = 1;
			if (length.y < 0)
				impact->upper_wall_face = 3;
			impact->upper_wall_length = ft_absf(length.y);
		}
	}
}

t_impact	*found_wall(t_impact *impact, t_vectorf length)
{
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
