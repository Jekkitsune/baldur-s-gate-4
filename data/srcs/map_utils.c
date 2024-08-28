/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:22:30 by fparis            #+#    #+#             */
/*   Updated: 2024/08/28 17:47:42 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	in_bound(t_map map, t_vector vec)
{
	return ((vec.x >= 0 && vec.x < map.size.x)
		&& (vec.y >= 0 && vec.y < map.size.y));
}

int	in_window(t_vector win_size, t_vector vec)
{
	return ((vec.x >= 0 && vec.x < win_size.x)
		&& (vec.y >= 0 && vec.y < win_size.y));
}
