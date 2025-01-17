/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_radius_team.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:50:08 by fparis            #+#    #+#             */
/*   Updated: 2025/01/17 01:08:44 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_cell_team(t_cell *cell, int team, int *score)
{
	t_list	*lst;

	lst = cell->entities;
	while (lst)
	{
		if (lst->content && ((t_entity *)lst->content)->sheet.alive)
		{
			if (((t_entity *)lst->content)->sheet.team == team)
				*score -= 10;
			else
				*score += 1;
		}
		lst = lst->next;
	}
}

void	check_radius_team(t_data *data, int team, t_spellinfo *info)
{
	int	i;
	int	i2;

	i = -1;
	while (++i < info->radius + 1)
	{
		i2 = info->pos.x - (info->radius - i) - 1;
		while (++i2 < info->pos.x + (info->radius - i))
		{
			if (in_bound(data->current_map, vec(i2, info->pos.y + i)))
			{
				check_cell_team(&data->current_map->arr[i2][info->pos.y + i],
					team, &info->nb);
				if (info->nb < 0)
					return ;
			}
			if (i != 0 && in_bound(data->current_map, vec(i2, info->pos.y - i)))
			{
				check_cell_team(&data->current_map->arr[i2][info->pos.y - i],
					team, &info->nb);
				if (info->nb < 0)
					return ;
			}
		}
	}
}

void	try_spell_range(t_data *data, t_spellinfo *info, t_spellinfo *current,
	t_vector pos)
{
	current->nb = 0;
	current->pos = pos;
	check_radius_team(data, info->caster->sheet.team, current);
	if (current->nb > info->nb)
	{
		info->nb = current->nb;
		info->pos = current->pos;
	}
}

void	try_all_spell_range(t_data *data, t_spellinfo *info)
{
	t_vector	i;
	t_vector	pos;
	t_spellinfo	current;

	i.x = 0;
	current.radius = info->radius;
	while (i.x < info->range + 1)
	{
		i.y = info->pos.x - (info->range - i.x);
		while (i.y < info->pos.x + (info->range - i.x))
		{
			pos = vec(i.y, info->pos.y + i.x);
			if (in_bound(data->current_map, pos)
				&& !has_obstacle_pos(data, info->pos, pos))
				try_spell_range(data, info, &current, pos);
			pos = vec(i.y, info->pos.y - i.x);
			if (i.x != 0 && in_bound(data->current_map, pos)
				&& !has_obstacle_pos(data, info->pos, pos))
				try_spell_range(data, info, &current, pos);
			i.y++;
		}
		i.x++;
	}
}

t_bool	get_best_spell_pos(t_data *data, t_spellinfo *spell, t_entity *caster)
{
	int			goal;
	t_spellinfo	info;

	if (spell->radius < 2)
		return (true);
	goal = ft_min(spell->radius, 3);
	info.pos = caster->pos;
	info.nb = 0;
	info.radius = spell->radius;
	info.range = spell->range;
	info.caster = caster;
	try_all_spell_range(data, &info);
	if (info.nb >= goal)
	{
		spell->pos = info.pos;
		return (true);
	}
	return (false);
}
