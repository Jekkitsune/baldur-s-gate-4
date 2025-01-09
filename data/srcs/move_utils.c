/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:03:41 by fparis            #+#    #+#             */
/*   Updated: 2025/01/07 14:11:18 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	correct_pos(t_data *data, t_vector *pos, t_vectorf *offset)
{
	while (offset->x >= data->scale)
	{
		pos->x++;
		offset->x = (double)-data->scale + (fabs(offset->x) - fabs((double)data->scale));
	}
	while (offset->x < -data->scale)
	{
		pos->x--;
		offset->x = (double)data->scale - (fabs(offset->x) - fabs((double)data->scale));
	}
	while (offset->y >= data->scale)
	{
		pos->y++;
		offset->y = (double)-data->scale + (fabs(offset->y) - fabs((double)data->scale));
	}
	while (offset->y < -data->scale)
	{
		pos->y--;
		offset->y = (double)data->scale - (fabs(offset->y) - fabs((double)data->scale));
	}
}
