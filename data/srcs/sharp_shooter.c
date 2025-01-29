/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sharp_shooter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:53:56 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 23:03:49 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	active_sharp_shooter(void *data_param, void *spell_param)
{
	t_data				*data;
	t_spellinfo			*spell;
	t_timer_property	*time_prop;

	data = data_param;
	spell = spell_param;
	if (!spell->caster || spell->caster->sheet.properties & sharp_shooter)
		return ;
	time_prop = new_timer_property(sharp_shooter, spell->caster, NULL, NULL);
	add_timer_property(data, time_prop, 1, true);
	show_info(data, "%s is in sharp shooter mode!", spell->caster->sheet.name);
}

void	init_sharp_shooter_button(t_data *data, t_button *button)
{
	button->spellinfo.range = 0;
	button->spellinfo.visible_target = true;
	button->spellinfo.effect = active_sharp_shooter;
	button->spellinfo.type = check_type;
	button->func = action_select;
	button->img = get_tex(data, "sharp_shoot_button");
	button->name = "Sharp shooter";
	button->description = "For this turn, -5 to attack rolls for +10 to damage \
to range attacks";
	button->spellinfo.target_self = true;
}
