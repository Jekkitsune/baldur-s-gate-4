/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:35:40 by fparis            #+#    #+#             */
/*   Updated: 2025/01/24 10:13:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_possession(t_data *data);
void	move_arrow(t_data *data);

void	move_spell(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	move_to(data, spell->caster, spell->pos);
}

void	init_move_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 0;
	button->spellinfo.range = 20;
	button->spellinfo.visible_target = false;
	button->spellinfo.effect = move_spell;
	button->spellinfo.type = move_type;
	button->func = action_select;
	button->img = get_tex(data, "move_button");
	button->spellinfo.anim = NULL;
	button->spellinfo.timer = 0;
	button->name = "Move";
	button->description = "Move to selected cell";
}

void	update_rotation(t_data *data, t_player *p)
{
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
	if (p->height > HEIGHT_CAP)
		p->height = HEIGHT_CAP;
	if (p->movement[5])
		p->height -= 50 * (data->scale * 2);
	if (p->height < -HEIGHT_CAP)
		p->height = -HEIGHT_CAP;
	if (p->angle > 2 * M_PI)
		p->angle = p->angle - (2 * M_PI);
	if (p->angle < 0)
		p->angle = (2 * M_PI) + p->angle;
	data->player.camera_plane.x = cosf(angle_add(data->player.angle, M_PI / 2));
	data->player.camera_plane.y = sinf(angle_add(data->player.angle, M_PI / 2));
	data->player.direction.x = cosf(data->player.angle);
	data->player.direction.y = sinf(data->player.angle);
}

void	move(t_data *data)
{
	t_player	*p;

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
	update_rotation(data, p);
	if (p->pitch > 1000)
		p->pitch = 1000;
	else if (p->pitch < -1000)
		p->pitch = -1000;
}
