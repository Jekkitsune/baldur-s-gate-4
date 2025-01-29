/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:29:54 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 10:53:55 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	add_to_inventory(t_data *data, t_entity *taker, t_entity *taken,
			t_bool no_equip);
void	open_other_inventory(t_data *data, t_button *button, t_entity *target,
			t_entity *caster);
int		other_inventory_hover_index(t_data *data);

void	fail_steal(t_data *data, t_entity *caster, t_entity *target,
	int result)
{
	int	dd;

	dd = 10 + modif(target->sheet.stats[WIS]) + target->sheet.level;
	check_attack_neutral(data, target);
	caster->sheet.inventory_open = false;
	show_info(data, "%s failed (%d) at stealing %s (%d)", \
caster->sheet.name, result, target->sheet.name, dd);
}

void	success_steal(t_data *data, t_entity *caster, t_entity *target,
	int result)
{
	int	dd;

	dd = 10 + modif(target->sheet.stats[WIS]) + target->sheet.level;
	show_info(data, "%s successfully (%d) robbed %s (%d)", \
caster->sheet.name, result, target->sheet.name, dd);
	caster->sheet.inventory_open = false;
}

void	steal(t_data *data, t_entity *caster, t_entity *target)
{
	int			index;
	int			rand_result;
	int			result;
	t_entity	*item;

	index = other_inventory_hover_index(data);
	if (index < 0 || index >= INVENTORY_SIZE)
		return ;
	item = target->sheet.inventory[index];
	if (!item)
		return ;
	rand_result = roll_one(20, 1);
	result = rand_result + caster->sheet.pb + modif(caster->sheet.stats[DEX]);
	if (result < 10 + modif(target->sheet.stats[WIS]) + target->sheet.level)
	{
		fail_steal(data, caster, target, result);
		return ;
	}
	success_steal(data, caster, target, result);
	if (add_to_inventory(data, caster, item, true))
		target->sheet.inventory[index] = NULL;
	if (index < NON_EQUIP)
		refresh_stats(data, target);
	caster->sheet.inventory_open = false;
}

void	steal_action(void *data_param, void *spell_param)
{
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	if (!spell->target || spell->target->sheet.type != living
		|| !apply_action_cost(data, spell))
		return ;
	open_other_inventory(data,
		get_button_pointer(spell->caster->sheet.buttons, "Steal"),
		spell->target, spell->caster);
}

void	init_steal_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 0;
	button->spellinfo.range = 1.5;
	button->spellinfo.visible_target = true;
	button->spellinfo.cost_action = 1;
	button->spellinfo.type = check_type;
	button->img = get_tex(data, "steal_button");
	button->func = action_select;
	button->spellinfo.effect = steal_action;
	button->name = "Steal";
	button->description = "Try to steal an item from entity if a DEX + PB test \
is succeeded against a DD of 10 + target's level + target's WIS";
}
