/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:35:40 by fparis            #+#    #+#             */
/*   Updated: 2024/11/21 02:27:26 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	rotate_focus(t_data *data)
{
	t_entity	*entity;

	if (!data->player.possession && !data->player.arrow)
		return ;
	entity = data->player.possession;
	if (data->player.arrow)
		entity = data->player.arrow;
	data->player.offset.x = entity->offset.x + (cosf(angle_add(data->player.angle, M_PI)) * data->player.focus_dist);
	data->player.offset.y = entity->offset.y + (sinf(angle_add(data->player.angle, M_PI)) * data->player.focus_dist);
	data->player.pos = entity->pos;

	correct_pos(data, &data->player.pos, &data->player.offset);
}

void	move_arrow(t_data *data)
{
	t_player 	*p;
	t_entity	*arrow;
	t_vectorf	offset;

	arrow = data->player.arrow;
	if (arrow)
	{
		p = &data->player;
		offset = arrow->offset;
		if (p->movement[0])
			change_pos(data, &offset, p->angle);
		if (p->movement[1])
			change_pos(data, &offset, p->angle - (M_PI / 2));
		if (p->movement[2])
			change_pos(data, &offset, p->angle + M_PI);
		if (p->movement[3])
			change_pos(data, &offset, p->angle + (M_PI / 2));
		if (p->movement[0] || p->movement[1] || p->movement[2] || p->movement[3])
			teleport_entity(data, arrow, arrow->pos, offset);
	}
}

void	move_possession(t_data *data)
{
	t_player 	*p;
	t_entity	*possession;
	t_vectorf	offset;

	possession = data->player.possession;
	if (possession && possession->possess_control)
	{
		p = &data->player;
		offset = possession->offset;
		if (p->movement[0])
			change_pos(data, &offset, p->angle);
		if (p->movement[1])
			change_pos(data, &offset, p->angle - (M_PI / 2));
		if (p->movement[2])
			change_pos(data, &offset, p->angle + M_PI);
		if (p->movement[3])
			change_pos(data, &offset, p->angle + (M_PI / 2));
		if (p->movement[0] || p->movement[1] || p->movement[2] || p->movement[3])
		{
			if (possession->current_anim && ft_strcmp(possession->current_anim->name, "walk"))
				change_anim(possession, "walk");
			if (p->movement[2])
				possession->angle = p->angle + (M_PI) * p->movement[2];
			else
				possession->angle = p->angle + (M_PI / 2) * -p->movement[1] + (M_PI / 2) * p->movement[3];
			angle_add(possession->angle, 0);
			teleport_entity(data, possession, possession->pos, offset);
		}
		else if (possession->current_anim && ft_strcmp(possession->current_anim->name, "idle"))
			change_anim(possession, "idle");
	}
}

void	move(t_data *data)
{
	t_player *p;

	p = &data->player;
	if (!data->player.focus_mode && !data->player.arrow)
	{
		if (p->movement[0])
			change_pos(data, &data->player.offset, p->angle);
		if (p->movement[1])
			change_pos(data, &data->player.offset, p->angle - (M_PI / 2));
		if (p->movement[2])
			change_pos(data, &data->player.offset, p->angle + M_PI);
		if (p->movement[3])
			change_pos(data, &data->player.offset, p->angle + (M_PI / 2));
		correct_pos(data, &data->player.pos, &data->player.offset);
	}
	else if (data->player.arrow)
		move_arrow(data);
	else if (data->player.possession)
		move_possession(data);

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



		if (p->angle > 2 * M_PI)
			p->angle = p->angle - (2 * M_PI);
		if (p->angle < 0)
			p->angle = (2 * M_PI) + p->angle;
		data->player.camera_plane.x = cosf(angle_add(data->player.angle, M_PI / 2));
		data->player.camera_plane.y = sinf(angle_add(data->player.angle, M_PI / 2));
		data->player.direction.x = cosf(data->player.angle);
		data->player.direction.y = sinf(data->player.angle);

	if (p->pitch > 1000)
		p->pitch = 1000;
	else if (p->pitch < -1000)
		p->pitch = -1000;
	get_all_rays(data);
}
