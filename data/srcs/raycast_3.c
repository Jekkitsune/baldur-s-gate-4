/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:06:13 by fparis            #+#    #+#             */
/*   Updated: 2025/01/22 03:03:44 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_fog(t_impact *impact, t_data *data, t_vectorf length)
{
	t_cell	*cell;

	cell = &data->current_map->arr[impact->wall_pos.x][impact->wall_pos.y];
	if (!impact->fog_color && cell->fog_color)
	{
		impact->fog_color = cell->fog_color;
		if (ft_absf(length.x) <= ft_absf(length.y))
			impact->fog_length = ft_absf(length.x);
		else
			impact->fog_length = ft_absf(length.y);
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
