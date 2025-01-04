/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fireball.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:30:20 by fparis            #+#    #+#             */
/*   Updated: 2025/01/04 01:48:48 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fireball_damage(void *data, t_entity *target, t_entity *caster, int nb)
{
	int	result;

	if (caster && target->sheet.hp)
	{
		result = roll_one(20, 1) + target->sheet.saving[DEX];
		if (result < caster->sheet.spell_dc)
		{
			show_info(data, "%s failed a DEX saving (%d) throw against %s's fireball (%d)\n", target->sheet.name, result, caster->sheet.name, caster->sheet.spell_dc);
			damage(data, target, nb);
		}
		else
		{
			show_info(data, "%s succeeded a DEX saving (%d) throw against %s's fireball (%d)\n", target->sheet.name, result, caster->sheet.name, caster->sheet.spell_dc);
			damage(data, target, nb / 2);
		}
	}
}

void	init_fireball_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 4;
	button->spellinfo.range = 12;
	button->spellinfo.visible_target = true;
	button->spellinfo.dice[D6] = 8;
	button->spellinfo.effect = fireball;
	button->func = action_select;
	button->img = get_tex(data, "fireball_button");
	button->spellinfo.anim = "cast";
	button->spellinfo.timer = 1.5;
	button->spellinfo.name = "Fireball";
}

void	fireball(void *data_param, void *spell_param)
{
	t_entity	*explosion;
	t_data		*data;
	t_spellinfo	*spell;

	data = data_param;
	spell = spell_param;
	explosion = spawn_entity(data, get_prefab(data, "explosion"), spell->pos, ft_strjoin("explosion", ""));
	add_active(data, explosion, expire);
	zone_effect(data, *spell, fireball_damage);
}
