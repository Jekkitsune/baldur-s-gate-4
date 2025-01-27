/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_possess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 01:18:56 by fparis            #+#    #+#             */
/*   Updated: 2025/01/25 08:48:20 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	possess_control(t_entity *entity, t_bool value)
{
	if (!entity)
		return ;
	entity->possess_control = value;
}

void	possess(t_data *data, t_entity *entity)
{
	remove_selector(data, false);
	if (!entity || !in_bound(data->current_map, entity->pos))
		return ;
	mlx_mouse_show();
	data->player.focus_mode = 1;
	data->player.focus_dist = 40;
	data->player.possession = entity;
	data->player.pos = data->player.possession->pos;
	data->player.offset = data->player.possession->offset;
	data->player.height = 0;
	data->player.pitch = 0;
}

void	unpossess(t_data *data)
{
	remove_selector(data, false);
	mlx_mouse_hide();
	data->player.focus_mode = 0;
	data->player.height = 0;
	data->player.pitch = 0;
	data->player.pos = data->player.possession->pos;
	data->player.offset = data->player.possession->offset;
	data->player.possession = NULL;
	data->player.active_button = NULL;
}

void	smooth_possess_effect(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (spell && spell->target)
	{
		data->player.focus_mode = 1;
		data->player.possession = spell->target;
	}
}

void	smooth_possess(t_data *data, t_entity *entity)
{
	t_entity	*mover;

	remove_selector(data, false);
	if (!data->player.possession)
	{
		possess(data, entity);
		return ;
	}
	mover = spawn_entity(data, get_prefab(data, "selector"),
			data->player.possession->pos, ft_strdup("selector"));
	if (!mover)
	{
		possess(data, entity);
		return ;
	}
	teleport_entity(data, mover, data->player.possession->pos,
		data->player.possession->offset);
	mover->visible = false;
	add_active(data, mover, projectile_ia);
	mover->behavior.target = entity;
	mover->behavior.spell.target = entity;
	mover->behavior.spell.effect = smooth_possess_effect;
	data->player.focus_mode = 1;
	data->player.possession = mover;
}
