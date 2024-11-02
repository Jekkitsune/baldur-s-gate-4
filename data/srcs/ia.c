/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:42:55 by fparis            #+#    #+#             */
/*   Updated: 2024/11/02 21:57:37 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	follow_player(void *arg_data, void *arg_entity)
{
	t_vectorf	move;
	t_data		*data;
	t_entity	*entity;
	t_vectorf	p_pos;
	float		speed;

	data = arg_data;
	entity = arg_entity;
	speed = 0.3;
	entity->true_pos.x = (entity->pos.x) * (data->scale * 2) + (entity->offset.x + data->scale);
	entity->true_pos.y = (entity->pos.y) * (data->scale * 2) + (entity->offset.y + data->scale);
	p_pos.x = data->player.pos.x * (data->scale * 2) + (data->player.offset.x + data->scale);
	p_pos.y = data->player.pos.y * (data->scale * 2) + (data->player.offset.y + data->scale);
	if (entity->true_pos.x < p_pos.x)
		move.x = speed;
	else if (entity->true_pos.x > p_pos.x)
		move.x = -speed;
	if (entity->true_pos.y < p_pos.y)
		move.y = speed;
	else if (entity->true_pos.y > p_pos.y)
		move.y = -speed;
	move_entity(data, entity, move);
}

void	ft_nothing(void *data, void *entity)
{
	if (data || entity)
		return ;
}
