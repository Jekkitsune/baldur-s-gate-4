/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_inventory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:52:38 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 00:00:32 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_button_inventory(t_button *button, t_entity *item);

void	drop(t_data *data, t_spellinfo *spell)
{
	t_list		*new_lst;
	t_entity	*drop;
	int			i;

	drop = spell->summon;
	if (!spell->caster || !drop)
		return ;
	i = spell->nb;
	if (i < 0 || i >= INVENTORY_SIZE)
		return ;
	new_lst = ft_lstnew(drop);
	if (!new_lst)
		return ;
	drop->offset = spell->pos_offset;
	drop->pos = spell->pos;
	drop->visible = true;
	ft_lstadd_front(&data->current_map->arr[drop->pos.x][drop->pos.y].entities,
		new_lst);
	if (drop->active)
		add_active(data, drop, drop->behavior.func);
	spell->caster->sheet.inventory[i] = NULL;
	refresh_stats(data, spell->caster);
	return ;
}

void	throw(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	drop(data, spell);
	spell->nb = spell->summon->sheet.weight / 3;
	if (get_dist(spell->pos, spell->caster->pos) > 2)
	{
		damage(data, spell->summon, spell->nb);
		if (spell->target)
			damage(data, spell->target, spell->nb);
	}
}

void	empty_button(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;
	t_button	*tmp;
	int			active_tmp;

	data = data_param;
	entity = entity_param;
	tmp = data->player.active_button;
	active_tmp = data->player.active_button->active;
	remove_selector(data, false);
	data->player.active_button = tmp;
	data->player.active_button->active = active_tmp;
	if (spell.caster)
		return ;
	return ;
}

void	set_inventory_button(t_entity *entity, int i)
{
	t_entity	*used;
	t_button	*button;

	if (i < 0 || i >= INVENTORY_SIZE)
		return ;
	used = entity->sheet.inventory[i];
	button = &entity->sheet.inventory_button;
	ft_bzero(button, sizeof(t_button));
	button->spellinfo.effect = NULL;
	button->spellinfo.radius = 0;
	button->spellinfo.nb = i;
	button->spellinfo.caster = entity;
	set_button_inventory(button, used);
}

t_button	*button_inventory(t_data *data, t_entity *entity)
{
	static int	last = -1;
	int			current;
	t_button	*button;

	current = inventory_hover_index(data);
	if (current == -1 || data->shown_other_inventory)
	{
		last = -1;
		return (NULL);
	}
	button = &entity->sheet.inventory_button;
	if (last == -1)
	{
		last = current;
		button->active = current + 1;
		set_inventory_button(entity, current);
	}
	else if (last >= 0)
	{
		inventory_swap(data, entity, last, current);
		last = -1;
	}
	return (button);
}
