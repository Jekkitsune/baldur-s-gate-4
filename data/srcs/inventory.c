/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:40:54 by fparis            #+#    #+#             */
/*   Updated: 2025/01/26 17:01:56 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		can_be_taken(t_entity *taker, t_entity *taken, t_bool no_equip);
void	add_gold(t_data *data, t_entity *to_add);

t_bool	add_to_inventory(t_data *data, t_entity *taker, t_entity *taken,
		t_bool no_equip)
{
	int	i;

	if (!taker || !taken)
		return (false);
	if (taken->sheet.type == gold && in_party(data, taker))
	{
		add_gold(data, taken);
		return (true);
	}
	i = can_be_taken(taker, taken, no_equip);
	if (i != -1 && taken->active)
		free(ft_lstpop(&data->current_map->active_entities, taken));
	if (i != -1 && i < INVENTORY_SIZE && !taker->sheet.inventory[i])
	{
		if (in_bound(data->current_map, taken->pos))
			free(ft_lstpop(&data->current_map->arr[taken->pos.x][taken->pos.y].\
			entities, taken));
		free_path(&taken->behavior.path);
		taken->pos.x = -1;
		taker->sheet.inventory[i] = taken;
		if (i < NON_EQUIP)
			refresh_stats(data, taker);
		return (true);
	}
	return (false);
}

void	take(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	apply_action_cost(data, spell);
	if (spell->target && spell->target->visible)
	{
		if (add_to_inventory(data, spell->caster, spell->target, false))
		{
			show_info(data, "%s picked up %s.\n", spell->caster->sheet.name,
				spell->target->sheet.name);
			return ;
		}
		show_info(data, "%s tried to pick up %s, but couldn't.\n",
			spell->caster->sheet.name, spell->target->sheet.name);
	}
}

void	open_inventory(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;

	(void)spell;
	data = data_param;
	entity = entity_param;
	data->player.active_button->active = 0;
	data->player.active_button = NULL;
	entity->sheet.inventory_open = !entity->sheet.inventory_open;
}

void	init_inventory_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 0;
	button->spellinfo.range = 0;
	button->spellinfo.visible_target = false;
	button->spellinfo.type = 0;
	button->img = get_tex(data, "inventory_button");
	button->func = open_inventory;
	button->name = NULL;
	button->description = NULL;
}
