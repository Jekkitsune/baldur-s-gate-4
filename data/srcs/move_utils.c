/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:03:41 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 20:07:28 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	correct_pos(t_data *data, t_vector *pos, t_vectorf *offset)
{
	while (offset->x >= data->scale)
	{
		pos->x++;
		offset->x = (double)-data->scale + (fabs(offset->x)
				- fabs((double)data->scale));
	}
	while (offset->x < -data->scale)
	{
		pos->x--;
		offset->x = (double)data->scale - (fabs(offset->x)
				- fabs((double)data->scale));
	}
	while (offset->y >= data->scale)
	{
		pos->y++;
		offset->y = (double)-data->scale + (fabs(offset->y)
				- fabs((double)data->scale));
	}
	while (offset->y < -data->scale)
	{
		pos->y--;
		offset->y = (double)data->scale - (fabs(offset->y)
				- fabs((double)data->scale));
	}
}

void	change_pos(t_data *data, t_vectorf *offset, float angle)
{
	t_vectorf	direc;

	if (angle > 2 * M_PI)
		angle = angle - (2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	direc.x = cosf(angle);
	direc.y = sinf(angle);
	offset->x += direc.x * data->player.speed;
	offset->y += direc.y * data->player.speed;
}

void	change_pos_collide(t_data *data, t_vector pos, t_vectorf *offset,
	float angle)
{
	t_vectorf	direc;

	if (angle > 2 * M_PI)
		angle = angle - (2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	direc.x = cosf(angle) * data->player.speed;
	direc.y = sinf(angle) * data->player.speed;
	if (offset->x + direc.x + HITBOX_VALUE > data->scale
		&& !is_empty_cell(data, vec(pos.x + 1, pos.y)))
		direc.x = data->scale - (offset->x + HITBOX_VALUE);
	else if (offset->x + direc.x - HITBOX_VALUE < -data->scale
		&& !is_empty_cell(data, vec(pos.x - 1, pos.y)))
		direc.x = -data->scale - (offset->x - HITBOX_VALUE);
	if (offset->y + direc.y + HITBOX_VALUE > data->scale
		&& !is_empty_cell(data, vec(pos.x, pos.y + 1)))
		direc.y = data->scale - (offset->y + HITBOX_VALUE);
	else if (offset->y + direc.y - HITBOX_VALUE < -data->scale
		&& !is_empty_cell(data, vec(pos.x, pos.y - 1)))
		direc.y = -data->scale - (offset->y - HITBOX_VALUE);
	offset->x += direc.x;
	offset->y += direc.y;
}
