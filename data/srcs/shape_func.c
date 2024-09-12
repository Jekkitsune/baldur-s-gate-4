/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:27:00 by fparis            #+#    #+#             */
/*   Updated: 2024/09/10 17:03:27 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_linfo	linfo(int color, int width, int (*check_shape)(t_data *data, t_vector vec), void *img)
{
	t_linfo	res;

	res.color = color;
	res.width = width;
	res.check = check_shape;
	res.img = img;
	return (res);
}

int	default_shape(__attribute__((unused)) t_data *data, __attribute__((unused)) t_vector vec)
{
	return (1);
}

int	in_minimap(t_data *data, t_vector vec)
{
	if (vec.x < 0 || vec.x > data->minimap.UI_size
		|| vec.y < 0 || vec.y > data->minimap.UI_size)
		return (0);
	return (1);
}
