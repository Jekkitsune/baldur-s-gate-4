/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spells_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 09:08:13 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 16:09:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	try_resist_spell(t_data *data, t_entity *entity, t_property prop,
	int stat)
{
	t_list				*lst;
	t_timer_property	*current;
	t_entity			*caster;

	if (check_properties(entity->sheet.properties, prop))
	{
		lst = entity->sheet.timer_property;
		while (lst)
		{
			current = lst->content;
			lst = lst->next;
			if (current && check_properties(current->property, prop))
			{
				caster = current->caster;
				if (caster && saving_throw(data, entity, stat,
					caster->sheet.spell_dc))
					pop_free_property(data, current);
			}
		}
	}
}

void	heal_entity(t_data *data, t_entity *entity, int heal)
{
	t_timer_property	*prop;

	if (!entity->sheet.alive)
		return ;
	if (heal < 0)
		heal = 0;
	entity->sheet.hp += heal;
	if (entity->sheet.hp > entity->sheet.max_hp)
		entity->sheet.hp = entity->sheet.max_hp;
	show_info(data, "%s was healed %d hp\n", entity->sheet.name, heal);
	prop = new_timer_property(heal_effect, entity, NULL, NULL);
	add_timer_property(data, prop, 0.3, false);
}

int	add_concentration(t_data *data, t_entity *entity)
{
	if (!(entity->sheet.properties & concentration_plus))
	{
		break_concentration(data, entity, 1);
		entity->sheet.concentration = 1;
		return (1);
	}
	if (entity->sheet.concentration == 2)
	{
		break_concentration(data, entity, 1);
		entity->sheet.concentration = 1;
		return (1);
	}
	else if (entity->sheet.concentration == 1)
	{
		break_concentration(data, entity, 2);
		entity->sheet.concentration = 2;
		return (2);
	}
	return (1);
}

void	damage_cell(t_data *data, t_vector pos, int nb)
{
	t_list		*lst;
	t_entity	*current;

	if (!in_bound(data->current_map, pos))
		return ;
	lst = data->current_map->arr[pos.x][pos.y].entities;
	while (lst)
	{
		current = lst->content;
		if (current && current->sheet.alive)
			damage(data, current, nb);
		lst = lst->next;
	}
}

void	zone_effect_cell(t_data *data, t_spellinfo *spel,
	void (*ef)(t_data *data, t_spellinfo *spel, t_cell *cell))
{
	int	i;
	int	i2;

	i = 0;
	while (i < spel->radius + 1)
	{
		i2 = spel->pos.x - (spel->radius - i);
		while (i2 < spel->pos.x + (spel->radius - i))
		{
			if (in_bound(data->current_map, vec(i2, spel->pos.y + i)))
				ef(data, spel, &data->current_map->arr[i2][spel->pos.y + i]);
			if (i != 0 && in_bound(data->current_map, vec(i2, spel->pos.y - i)))
				ef(data, spel, &data->current_map->arr[i2][spel->pos.y - i]);
			i2++;
		}
		i++;
	}
}
