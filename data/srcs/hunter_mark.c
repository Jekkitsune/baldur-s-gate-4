/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hunter_mark.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:42:11 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:05:41 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_entity	*get_hunter_mark_caster(t_entity *target)
{
	t_list				*lst;
	t_timer_property	*prop;

	if (!target || !(target->sheet.properties & hunter_marked))
		return (NULL);
	lst = target->sheet.timer_property;
	while (lst)
	{
		prop = lst->content;
		if (prop && prop->property & hunter_marked
			&& prop->caster)
			return (prop->caster);
		lst = lst->next;
	}
	return (NULL);
}

void	check_hunter_mark(t_data *data, t_spellinfo *spell)
{
	int		dmg;

	if (get_hunter_mark_caster(spell->target) != spell->caster)
		return ;
	dmg = roll(spell->caster->sheet.class->\
	level[ft_min(spell->caster->sheet.level \
	- 1, MAX_LEVEL - 1)].current_bonus_dice);
	show_info(data, "%s hunter's mark dealt %d damage",
		spell->caster->sheet.name, dmg);
	if (spell->caster->sheet.class)
		damage(data, spell->target, dmg);
}

void	hunter_mark(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->target || !apply_action_cost(data, spell))
		return ;
	show_info(data, "%s cast Hunter's mark!", spell->caster->sheet.name);
	if (spell->caster->sheet.properties & master_hunter)
		time_prop = new_timer_property(hunter_marked | marked_ac,
				spell->target, spell->caster, NULL);
	else
		time_prop = new_timer_property(hunter_marked,
				spell->target, spell->caster, NULL);
	if (time_prop)
	{
		time_prop->id_concentration = spell->concentration;
		add_timer_property(data, time_prop, 20, true);
	}
}

void	init_hunter_mark_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 10;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = hunter_mark;
	button->spellinfo.type = debuff;
	button->spellinfo.concentration = 1;
	button->spellinfo.cost_bonus = 1;
	button->spellinfo.cost_spell_slot = 1;
	button->func = action_select;
	button->img = get_tex(data, "hunter_mark_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1;
	button->name = "Hunter's mark";
	button->description = "Set a mark on the target, +1D6 dmg caster's attacks \
on marked target";
	button->spellinfo.can_be_silenced = true;
	if (!button->user || !button->user->sheet.class)
	{
		button->spellinfo.dice[6] = 1;
		return ;
	}
	if (button->user->sheet.class)
		copy_dice(button->spellinfo.dice,
			button->user->sheet.class->level[ft_min(button->user->sheet.level
				- 1, MAX_LEVEL - 1)].current_bonus_dice);
}
