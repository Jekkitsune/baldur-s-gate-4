/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:35:40 by fparis            #+#    #+#             */
/*   Updated: 2024/09/10 15:58:31 by fparis           ###   ########.fr       */
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

void	move(t_data *data)
{
	t_player *p;

	p = &data->player;
	if (p->movement[0])
		change_pos(data, p->angle);
	if (p->movement[1])
		change_pos(data, p->angle - (M_PI / 2));
	if (p->movement[2])
		change_pos(data, p->angle + M_PI);
	if (p->movement[3])
		change_pos(data, p->angle + (M_PI / 2));
	
	if (p->rotation[0])
		p->angle -= 0.1;
	if (p->rotation[1])
		p->angle += 0.1;

	if (p->offset.x > data->scale)
	{
		p->pos.x++;
		p->offset.x = -data->scale + (ft_abs(p->offset.x) - ft_abs(data->scale));
	}
	else if (p->offset.x < -data->scale)
	{
		p->pos.x--;
		p->offset.x = data->scale - (ft_abs(p->offset.x) - ft_abs(data->scale));
	}
	if (p->offset.y > data->scale)
	{
		p->pos.y++;
		p->offset.y = -data->scale + (ft_abs(p->offset.y) - ft_abs(data->scale));
	}
	else if (p->offset.y < -data->scale)
	{
		p->pos.y--;
		p->offset.y = data->scale - (ft_abs(p->offset.y) - ft_abs(data->scale));
	}

	if (p->rotation[0] || p->rotation[1])
	{
		if (p->angle > 2 * M_PI)
			p->angle = p->angle - (2 * M_PI);
		if (p->angle < 0)
			p->angle = (2 * M_PI) + p->angle;
		data->player.camera_plane.x = cosf(angle_add(data->player.angle, M_PI / 2));
		data->player.camera_plane.y = sinf(angle_add(data->player.angle, M_PI / 2));
		data->player.direction.x = cosf(data->player.angle);
		data->player.direction.y = sinf(data->player.angle);
	}
	//if (p->movement[0] || p->movement[1] || p->movement[2] || p->movement[3] || p->rotation[0] || p->rotation[1])
		get_all_rays(data);
}
