/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmassoni <gmassoni@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:57:00 by gmassoni          #+#    #+#             */
/*   Updated: 2025/01/29 13:57:01 by gmassoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	in_bound(t_map *map, t_vector vec)
{
	return ((vec.x >= 0 && vec.x < map->size.x)
		&& (vec.y >= 0 && vec.y < map->size.y));
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
