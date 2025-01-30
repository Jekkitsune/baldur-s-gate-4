/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:01:11 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 16:06:41 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_more_properties_stat(t_entity *entity, t_property prop);

void	check_was_dominated(t_data *data, t_entity *entity)
{
	if (entity->behavior.was_dominated
		&& !(entity->sheet.properties & dominated))
	{
		entity->behavior.was_dominated = false;
		entity->sheet.team = entity->sheet.default_team;
		if (!entity->behavior.dominated_player)
		{
			leave_party(data, entity);
			entity->possess_control = false;
		}
		else if (entity->behavior.dominated_player)
			entity->possess_control = true;
	}
	if (!(entity->sheet.properties & dominated))
		entity->sheet.team = entity->sheet.default_team;
}

void	set_properties_stat(t_entity *entity, t_property prop)
{
	if (prop & unarmored_defense)
		entity->sheet.ac += modif(entity->sheet.stats[CON]);
	if (prop & spiritual_defense)
		entity->sheet.ac += modif(entity->sheet.stats[WIS]);
	if (prop & giant)
	{
		entity->sheet.stats[STR] += 2;
		entity->sheet.ac += 2;
		entity->size_scale = 1.5;
	}
	if (prop & shadow_sword_prop)
		entity->sheet.atk_bonus = entity->sheet.spell_bonus;
	if (prop & difficult_terrain)
		entity->sheet.speed /= 2;
	if (prop & (restrained))
		entity->sheet.speed = 0;
	if (check_properties(prop, range | master_archer))
		entity->sheet.atk_bonus += 2;
	if (prop & acid)
		entity->sheet.ac -= 2;
	if (prop & marked_ac)
		entity->sheet.ac -= 2;
	set_more_properties_stat(entity, prop);
}

void	add_prop_refresh(t_data *data, t_entity *entity, t_property prop)
{
	entity->sheet.properties |= prop;
	refresh_stats(data, entity);
}

t_property	get_property(t_data *data, char *name)
{
	t_property	i;

	(void)data; //a changer!!
	i = 0;
	while (i < NB_PROPERTIES)
	{
		if (!ft_strcmp(PROPERTIES_TAB[i], name))
			return (1ULL << i);
		i++;
	}
	return (0);
}

t_bool	check_properties(t_property properties, t_property check)
{
	return ((properties & check) == check);
}
