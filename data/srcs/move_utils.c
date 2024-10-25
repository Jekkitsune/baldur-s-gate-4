/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:03:41 by fparis            #+#    #+#             */
/*   Updated: 2024/10/17 22:26:34 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	correct_pos(t_data *data, t_vector *pos, t_vectorf *offset)
{
	while (offset->x >= data->scale)
	{
		pos->x++;
		offset->x = -data->scale + (ft_abs(offset->x) - ft_abs(data->scale));
	}
	while (offset->x < -data->scale)
	{
		pos->x--;
		offset->x = data->scale - (ft_abs(offset->x) - ft_abs(data->scale));
	}
	while (offset->y >= data->scale)
	{
		pos->y++;
		offset->y = -data->scale + (ft_abs(offset->y) - ft_abs(data->scale));
	}
	while (offset->y < -data->scale)
	{
		pos->y--;
		offset->y = data->scale - (ft_abs(offset->y) - ft_abs(data->scale));
	}
}
