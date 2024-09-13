/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:35:40 by fparis            #+#    #+#             */
/*   Updated: 2024/09/13 23:30:27 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	change_pos(t_data *data, float angle)
{
	t_vectorf	direc;
	t_player 	*p;

	p = &data->player;
	if (angle > 2 * M_PI)
		angle = angle - (2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	direc.x = cosf(angle);
	direc.y = sinf(angle);
	p->offset.x += direc.x * p->speed;
	p->offset.y += direc.y * p->speed;
}

void	rotate_focus(t_data *data)
{
	data->player.offset.x = data->player.target_offset.x + (cosf(angle_add(data->player.angle, M_PI)) * data->player.focus_dist);
	data->player.offset.y = data->player.target_offset.y + (sinf(angle_add(data->player.angle, M_PI)) * data->player.focus_dist);
	data->player.pos = data->player.target_pos;

	correct_pos(data, &data->player.pos, &data->player.offset);
}

void	move(t_data *data)
{
	t_player *p;

	p = &data->player;
	if (data->player.focus_mode)
	{
		if (p->movement[0] && p->focus_dist > 15)
			p->focus_dist -= p->speed;
		if (p->movement[2] && p->focus_dist < 100)
			p->focus_dist += p->speed;
	}
	else
	{
		if (p->movement[0])
			change_pos(data, p->angle);
		if (p->movement[1])
			change_pos(data, p->angle - (M_PI / 2));
		if (p->movement[2])
			change_pos(data, p->angle + M_PI);
		if (p->movement[3])
			change_pos(data, p->angle + (M_PI / 2));
	}
	
	if (p->rotation[1])
		p->angle -= 0.1;
	if (p->rotation[3])
		p->angle += 0.1;
	if (p->rotation[0])
		p->pitch += 50;
	if (p->rotation[2])
		p->pitch -= 50;

	if (p->movement[4])
		p->height += 50 * (data->scale * 2);
	if (p->movement[5])
		p->height -= 50 * (data->scale * 2);
		
	correct_pos(data, &data->player.pos, &data->player.offset);

	// if (p->rotation[1] || p->rotation[3])
	// {
		if (p->angle > 2 * M_PI)
			p->angle = p->angle - (2 * M_PI);
		if (p->angle < 0)
			p->angle = (2 * M_PI) + p->angle;
		data->player.camera_plane.x = cosf(angle_add(data->player.angle, M_PI / 2));
		data->player.camera_plane.y = sinf(angle_add(data->player.angle, M_PI / 2));
		data->player.direction.x = cosf(data->player.angle);
		data->player.direction.y = sinf(data->player.angle);
	// }
	get_all_rays(data);
}
