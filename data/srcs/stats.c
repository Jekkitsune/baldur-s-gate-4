/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:28:28 by fparis            #+#    #+#             */
/*   Updated: 2025/01/27 04:15:20 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_save_pb(t_entity *entity);
void	set_properties_stat(t_entity *entity, t_property prop);
void	init_all_buttons(t_data *data, t_entity *entity);
void	check_was_dominated(t_data *data, t_entity *entity);

void	reset_stats(t_entity *entity, t_entity *prefab)
{
	entity->sheet.max_hp = prefab->sheet.max_hp;
	entity->sheet.pb = prefab->sheet.pb;
	entity->sheet.ac = prefab->sheet.ac;
	entity->sheet.atk_bonus = prefab->sheet.atk_bonus;
	entity->sheet.weight = prefab->sheet.weight;
	entity->sheet.carry = prefab->sheet.carry;
	entity->sheet.spell_bonus = prefab->sheet.spell_bonus;
	entity->sheet.spell_dc = prefab->sheet.spell_dc;
	entity->sheet.speed = prefab->sheet.speed;
	entity->sheet.properties = prefab->sheet.properties;
	entity->sheet.nb_attack = prefab->sheet.nb_attack;
	entity->size_scale = prefab->size_scale;
	copy_stat_tab(entity->sheet.stats, prefab->sheet.stats, 6);
	copy_stat_tab(entity->sheet.saving, prefab->sheet.saving, 6);
}

void	add_stat(t_entity *entity, t_entity *item)
{
	entity->sheet.max_hp += item->sheet.max_hp;
	entity->sheet.pb += item->sheet.pb;
	entity->sheet.ac += item->sheet.ac;
	entity->sheet.atk_bonus += item->sheet.atk_bonus;
	entity->sheet.weight += item->sheet.weight;
	entity->sheet.carry += item->sheet.carry;
	entity->sheet.spell_bonus += item->sheet.spell_bonus;
	entity->sheet.spell_dc += item->sheet.spell_dc;
	entity->sheet.speed += item->sheet.speed;
	entity->sheet.properties |= item->sheet.properties;
	entity->sheet.nb_attack += item->sheet.nb_attack;
	sum_stat_tab(entity->sheet.stats, item->sheet.stats, 6);
	sum_stat_tab(entity->sheet.saving, item->sheet.saving, 6);
}

void	add_weight(t_entity *entity)
{
	int			i;
	t_entity	*current;

	i = NON_EQUIP;
	while (i < INVENTORY_SIZE)
	{
		current = entity->sheet.inventory[i++];
		if (current)
			entity->sheet.weight += current->sheet.weight;
	}
}

void	check_inventory_stats(t_entity *entity)
{
	int			i;
	t_entity	*current;

	i = 0;
	while (i < NON_EQUIP)
	{
		current = entity->sheet.inventory[i++];
		if (current)
			add_stat(entity, current);
	}
	add_weight(entity);
}

void	refresh_stats(t_data *data, t_entity *entity)
{
	t_entity	*prefab;

	if (!entity || !entity->sheet.prefab || entity->sheet.type != living)
		return ;
	prefab = entity->sheet.prefab;
	reset_stats(entity, prefab);
	refresh_entity_class(entity, entity->sheet.level);
	check_inventory_stats(entity);
	set_all_entity_timer_prop(data, entity);
	set_properties_stat(entity, entity->sheet.properties);
	set_save_pb(entity);
	init_all_buttons(data, entity);
	check_was_dominated(data, entity);
}
