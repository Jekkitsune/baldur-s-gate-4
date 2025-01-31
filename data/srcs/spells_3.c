/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spells_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:02:12 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 23:39:25 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_entity	*get_hunter_mark_caster(t_entity *target);

void	call_neutral(__attribute__((unused)) void *data, t_entity *target,
	__attribute__((unused)) t_entity *caster, __attribute__((unused)) int nb)
{
	if (target && target->sheet.team == 0 && !target->possess_control)
	{
		target->sheet.default_team = 2;
		target->sheet.team = 2;
	}
}

void	check_attack_neutral(t_data *data, t_entity *entity)
{
	t_spellinfo	info;

	if (entity->sheet.default_team == 0 && !entity->possess_control)
	{
		entity->sheet.default_team = 2;
		entity->sheet.team = 2;
		info.radius = 10;
		info.pos = entity->pos;
		info.caster = entity;
		info.nb = entity->sheet.team;
		zone_effect(data, info, call_neutral);
	}
}

void	concentration_save(t_data *data, t_entity *entity, int dmg)
{
	t_list	*lst;

	lst = entity->sheet.timer_concentration;
	while (lst && lst->content
		&& !((t_timer_property *)lst->content)->id_concentration)
		lst = lst->next;
	if (!lst || !lst->content)
		return ;
	if (entity->sheet.hp <= 0
		|| !saving_throw(data, entity, CON, ft_max(10, dmg / 2)))
	{
		break_concentration(data, entity, 0);
		show_info(data, "%s lost his concentration!", entity->sheet.name);
	}
	else
		show_info(data, "%s kept his concentration!", entity->sheet.name);
}

void	kill(t_data *data, t_entity *entity)
{
	if (!entity)
		return ;
	if (entity->sheet.team && entity->sheet.exp > 0)
		data->round_manager.party_exp += entity->sheet.exp;
	if (get_hunter_mark_caster(entity))
		get_hunter_mark_caster(entity)->sheet.spell_slot[0]++;
	leave_combat(data, entity);
	change_anim(entity, "dead", false);
	entity->sheet.alive = false;
	entity->behavior.func = death;
}
