/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 04:46:54 by fparis            #+#    #+#             */
/*   Updated: 2025/01/06 03:02:09 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	refresh_level_buttons(t_entity *entity, int i_level, int *button_nb)
{
	int		i;
	t_class	*class;

	i = 0;
	class = entity->sheet.class;
	while (*button_nb < NB_BUTTON - 1 && i < LEVEL_NB_BUTTON)
	{
		if (class->level[i_level].buttons[i].func)
		{
			entity->sheet.buttons[*button_nb] = class->level[i_level].buttons[i];
			*button_nb += 1;
		}
		i++;
	}
}

void	refresh_entity_class(t_entity *entity, int level, int *button_nb)
{
	int		i_level;
	t_class	*class;

	class = entity->sheet.class;
	if (!class)
		return ;
	i_level = 0;
	while (i_level < level && i_level < MAX_LEVEL)
	{
		refresh_level_buttons(entity, i_level, button_nb);
		entity->sheet.pb += class->level[i_level].add_pb;
		entity->sheet.max_hp += class->level[i_level].add_pv;
		entity->sheet.properties |= class->level[i_level].properties;
		sum_stat_tab(entity->sheet.stats, class->level[i_level].add_stats);
		i_level++;
	}
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

void	init_wizard_class(t_data *data)
{
	t_class	*class;

	class = ft_calloc(sizeof(t_class), 1);
	if (!class)
		return ;
	class->name = "wizard";
	init_fireball_button(data, &class->level[0].buttons[0]);
	add_class(&data->class_lst, class);
}

void	init_all_classes(t_data *data)
{
	init_wizard_class(data);
}
