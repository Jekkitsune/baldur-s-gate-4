/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:27:00 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 12:32:02 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_linfo	linfo(int color, int width,
	int (*check_shape)(t_data *data, t_vector vec))
{
	t_linfo	res;

	res.color = color;
	res.width = width;
	res.check = check_shape;
	return (res);
}

int	default_shape(__attribute__((unused)) t_data *data,
	__attribute__((unused)) t_vector vec)
{
	return (1);
}

int	in_minimap(t_data *data, t_vector vec)
{
	if (vec.x < data->minimap.pos.x || vec.x >= data->minimap.ui_size
		+ data->minimap.pos.x || vec.y < data->minimap.pos.y || vec.y
		>= data->minimap.ui_size + data->minimap.pos.y)
		return (0);
	return (1);
}
