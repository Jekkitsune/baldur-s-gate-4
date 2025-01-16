/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 23:37:10 by fparis            #+#    #+#             */
/*   Updated: 2025/01/16 20:16:59 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_timer_effect(t_data *data, t_spellinfo spell, float time,
	t_bool in_round)
{
	t_timer_effect	*res;
	t_list			*new;

	res = ft_calloc(sizeof(t_timer_effect), 1);
	if (!res)
		return ;
	new = ft_lstnew(res);
	if (!new)
	{
		free(res);
		return ;
	}
	res->in_round = in_round;
	res->spell = spell;
	res->duration = time;
	if (!in_round)
		res->duration = (float)time * 1000000.0;
	ft_lstadd_front(&data->timer_effect, new);
}

void	update_all_timer_effects(t_data *data, t_bool round)
{
	t_list			*lst;
	t_list			*tmp;
	t_timer_effect	*current;

	lst = data->timer_effect;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		current->duration -= data->frame_time;
		if ((round && current->in_round && --current->duration <= 0)
			|| (!current->in_round && current->duration <= 0))
		{
			current->spell.effect(data, &current->spell);
			tmp = ft_lstpop(&data->timer_effect, current);
			free(tmp->content);
			free(tmp);
		}
	}
}

void	clear_entity_timer_effect(t_data *data, t_entity *entity)
{
	t_list			*lst;
	t_list			*tmp;
	t_timer_effect	*current;

	lst = data->timer_effect;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current && (current->spell.caster == entity
				|| current->spell.target == entity
				|| current->spell.summon == entity))
		{
			tmp = ft_lstpop(&data->timer_effect, current);
			free(tmp->content);
			free(tmp);
		}
	}
}
