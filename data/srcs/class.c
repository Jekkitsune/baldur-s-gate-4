/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 04:46:54 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 15:21:25 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		class_bonus_dmg(t_entity *entity)
{
	t_class	*class;
	int		level;

	class = entity->sheet.class;
	if (!class)
		return (0);
	level = ft_min(entity->sheet.level - 1, MAX_LEVEL - 1);
	return(roll(class->level[level].current_bonus_dice));
}

void	refresh_entity_class(t_entity *entity, int level)
{
	int		i_level;
	t_class	*class;

	class = entity->sheet.class;
	if (!class)
		return ;
	i_level = 0;
	while (i_level < level && i_level < MAX_LEVEL)
	{
		entity->sheet.pb += class->level[i_level].add_pb;
		entity->sheet.max_hp += class->level[i_level].add_pv;
		entity->sheet.properties |= class->level[i_level].properties;
		entity->sheet.nb_attack += class->level[i_level].add_nb_attack;
		entity->sheet.speed += class->level[i_level].add_speed;
		sum_stat_tab(entity->sheet.stats, class->level[i_level].add_stats, 6);
		i_level++;
	}
	entity->sheet.spell_bonus = entity->sheet.prefab->sheet.spell_bonus
		+ entity->sheet.pb + modif(entity->sheet.stats[class->cast_stat]);
	entity->sheet.spell_dc = entity->sheet.prefab->sheet.spell_dc
		+ entity->sheet.pb + modif(entity->sheet.stats[class->cast_stat]);
}

t_class	*get_class(t_list *class_lst, char *name)
{
	t_list	*lst;

	lst = class_lst;
	while (lst)
	{
		if (lst->content && !ft_strcmp(((t_class *)lst->content)->name, name))
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

void	add_class(t_list **class_lst, t_class *class)
{
	t_list	*lst;

	if (!class)
		return ;
	lst = ft_lstnew(class);
	if (!lst)
	{
		free(class);
		return ;
	}
	ft_lstadd_front(class_lst, lst);
}
