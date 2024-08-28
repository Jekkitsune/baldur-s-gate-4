/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:35:40 by fparis            #+#    #+#             */
/*   Updated: 2024/08/28 20:14:08 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move(t_data *data)
{
	t_player *p;

	p = &data->player;
	//printf("pos:x %d, y: %d\nmovement: %d, %d, %d, %d\noffset: %d, %d\n", p->pos.x, p->pos.y, p->movement[0], p->movement[1], p->movement[2], p->movement[3], p->offset.x, p->offset.y);
	//printf("angle: %f\n", p->angle);
	if (p->movement[0])
		p->offset.y -= p->speed;
	if (p->movement[1])
		p->offset.x -= p->speed;
	if (p->movement[2])
		p->offset.y += p->speed;
	if (p->movement[3])
		p->offset.x += p->speed;
	
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
	}
	if (p->movement[0] || p->movement[1] || p->movement[2] || p->movement[3] || p->rotation[0] || p->rotation[1])
		get_all_rays(data);
}
