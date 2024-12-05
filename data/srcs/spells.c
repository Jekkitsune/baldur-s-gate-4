/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spells.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:49:41 by fparis            #+#    #+#             */
/*   Updated: 2024/12/04 20:14:41 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spell_info(t_spellinfo *spell, void (*effect)(void *data, t_entity *target, t_entity *caster, int nb),
	t_vector pos, t_entity *caster)
{
	spell->nb = 0;
	spell->effect = effect;
	spell->pos = pos;
	spell->caster = caster;
}

void	apply_cell(t_data *data, t_cell cell, t_spellinfo spell)
{
	t_list	*lst;

	lst = cell.entities;
	while (lst)
	{
		spell.effect(data, lst->content, spell.caster, spell.nb);
		lst = lst->next;
	}
}

void	zone_effect(t_data *data, t_spellinfo spell)
{
	int	i;
	int	i2;
	int	line_size;

	i = 0;
	while (i < spell.radius + 1)
	{
		i2 = spell.pos.x - (spell.radius - i);
		printf("%d\n", i2);
		while (i2 < spell.pos.x + (spell.radius - i))
		{
			if (in_bound(*data->current_map, vec(i2, spell.pos.y + i)))
				apply_cell(data, data->current_map->arr[i2][spell.pos.y + i], spell);
			if (i != 0 && in_bound(*data->current_map, vec(i2, spell.pos.y - i)))
				apply_cell(data, data->current_map->arr[i2][spell.pos.y - i], spell);
			i2++;
		}
		i++;
	}
}

void	damage(t_data *data, t_entity *entity, int dmg)
{
	if (entity->sheet.hp <= 0)
		return ;
	entity->sheet.hp -= dmg;
	printf("%s took %d damage\n", entity->sheet.name, dmg);
	if (entity->sheet.hp <= 0)
	{
		change_anim(entity, "dead");
		entity->sheet.alive = false;
		entity->behavior = death;
	}
}
