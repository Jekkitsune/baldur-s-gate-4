/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 23:37:10 by fparis            #+#    #+#             */
/*   Updated: 2025/01/03 17:55:59 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_timer_effect(t_data *data, t_spellinfo spell, float time, t_bool in_round)
{
	t_timer_effect	*res;
	t_list			*new;
	struct timeval 	tv;

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
	{
		gettimeofday(&tv, NULL);
		res->start = tv;
		res->duration = (float)time * 1000000.0;
	}
	ft_lstadd_front(&data->timer_effect, new);
}

void	update_all_timer_effects(t_data *data)
{
	t_list			*lst;
	t_list			*tmp;
	t_timer_effect	*current;
	struct timeval 	tv;

	gettimeofday(&tv, NULL);
	lst = data->timer_effect;
	while (lst)
	{
		current = lst->content;
		lst = lst->next;
		if (current && (current->in_round && --current->duration <= 0) || ((tv.tv_sec - current->start.tv_sec) * 1000000 + tv.tv_usec - current->start.tv_usec > current->duration))
		{
			current->spell.effect(data, &current->spell);
			tmp = ft_lstpop(&data->timer_effect, current);
			free(tmp->content);
			free(tmp);
		}
	}
}
