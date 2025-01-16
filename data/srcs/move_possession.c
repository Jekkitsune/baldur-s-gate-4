/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_possession.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 20:03:36 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 20:36:20 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_focus(t_data *data)
{
	t_entity	*entity;

	if (!data->player.possession && !data->player.arrow)
		return ;
	entity = data->player.possession;
	if (data->player.arrow)
		entity = data->player.arrow;
	data->player.offset.x = entity->offset.x
		+ (cosf(angle_add(data->player.angle, M_PI)) * data->player.focus_dist);
	data->player.offset.y = entity->offset.y
		+ (sinf(angle_add(data->player.angle, M_PI)) * data->player.focus_dist);
	data->player.pos = entity->pos;
	correct_pos(data, &data->player.pos, &data->player.offset);
}

void	move_arrow(t_data *data)
{
	t_player	*p;
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
		if (p->movement[0] || p->movement[1]
			|| p->movement[2] || p->movement[3])
			teleport_entity(data, arrow, arrow->pos, offset);
	}
}

void	collide_possession(t_data *data, t_player *p, t_entity *possession,
	t_vectorf *offset)
{
	if (p->movement[0])
		change_pos_collide(data, possession->pos, offset, p->angle);
	if (p->movement[1])
		change_pos_collide(data, possession->pos,
			offset, p->angle - (M_PI / 2));
	if (p->movement[2])
		change_pos_collide(data, possession->pos, offset, p->angle + M_PI);
	if (p->movement[3])
		change_pos_collide(data, possession->pos,
			offset, p->angle + (M_PI / 2));
}

void	update_possession_pos(t_data *data, t_player *p, t_entity *possession,
	t_vectorf offset)
{
	if (p->movement[0] || p->movement[1]
		|| p->movement[2] || p->movement[3])
	{
		if (possession->current_anim
			&& ft_strcmp(possession->current_anim->name, "walk"))
			change_anim(possession, "walk", true);
		if (p->movement[2])
			possession->angle = p->angle + (M_PI) * p->movement[2];
		else
			possession->angle = p->angle + (M_PI / 2) * -p->movement[1]
				+ (M_PI / 2) * p->movement[3];
		angle_add(possession->angle, 0);
		teleport_entity(data, possession, possession->pos, offset);
	}
	else if (possession->current_anim && !possession->behavior.path
		&& !ft_strcmp(possession->current_anim->name, "walk"))
		change_anim(possession, "idle", true);
}

void	move_possession(t_data *data)
{
	t_player	*p;
	t_entity	*possession;
	t_vectorf	offset;

	possession = data->player.possession;
	if (!data->round_manager.combat && possession && !possession->anim_no_move
		&& possession->possess_control && possession->sheet.alive)
	{
		p = &data->player;
		offset = possession->offset;
		collide_possession(data, p, possession, &offset);
		update_possession_pos(data, p, possession, offset);
	}
}
