/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fireball.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:30:20 by fparis            #+#    #+#             */
/*   Updated: 2024/12/07 21:51:43 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fireball_damage(void *data, t_entity *target, t_entity *caster, int nb)
{
	if (caster && target)
		damage(data, target, nb);
}

void	init_fireball_button(t_data *data, t_button *button)
{
	button->spellinfo.radius = 4;
	button->spellinfo.range = 12;
	button->spellinfo.visible_target = true;
	button->func = fireball;
	button->img = get_tex(data, "fireball_button");
}

void	fireball(void *data_param, void *entity_param, t_spellinfo spell)
{
	t_data		*data;
	t_entity	*entity;
	t_vector	pos;
	t_entity	*explosion;

	data = data_param;
	entity = entity_param;
	if (!data->player.arrow)
		select_target(data);
	if (!check_dist_obstacle(data, entity, spell.range, spell.visible_target)
		|| !confirm(data->player.active_button))
		return ;
	pos = data->player.arrow->pos;
	remove_selector(data);
	explosion = spawn_entity(data, get_prefab(data, "explosion"), pos, ft_strjoin("explosion", ""));
	add_active(data, explosion, expire);
	change_anim(explosion, "idle");
	spell_info(&spell, fireball_damage, pos, entity);
	spell.nb = 25;
	zone_effect(data, spell);
}
