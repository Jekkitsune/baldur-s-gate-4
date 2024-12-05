/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:48:43 by fparis            #+#    #+#             */
/*   Updated: 2024/11/30 10:48:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*get_correct_tex(t_entity *entity, int face)
{
	char	*name;
	int		index;

	name = NULL;
	if (!entity->current_anim)
		return (entity->tex[face]);
	if (face == 1)
		name = ft_strjoin(entity->current_anim->name, "_sidel");
	else if (face == 2)
		name = ft_strjoin(entity->current_anim->name, "_back");
	else if (face == 3)
		name = ft_strjoin(entity->current_anim->name, "_sider");
	if (name)
	{
		index = get_anim_index(entity, name);
		free(name);
		if (index != -1 && entity->anim_index < entity->anim[index].size)
			return (entity->anim[index].tab[entity->anim_index]);
	}
	return (entity->current_anim->tab[entity->anim_index]);
}

int	get_anim_index(t_entity *entity, char *name)
{
	int	i;

	i = 0;
	if (!name || !entity)
		return (-1);
	while (i < entity->nb_anim)
	{
		if (ft_strcmp(name, entity->anim[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	change_anim(t_entity *entity, char *name)
{
	int	index;

	index = get_anim_index(entity, name);
	if (index == -1)
		return ;
	entity->current_anim = &entity->anim[index];
	entity->anim_index = 0;
	entity->anim_clock = entity->current_anim->interval;
}

void	continue_anim(t_data *data, t_entity *entity)
{
	t_animation	*current;

	if (!entity->current_anim)
		return ;
	current = entity->current_anim;
	entity->anim_clock--;
	if (entity->anim_clock < 0)
	{
		entity->anim_index++;
		if (entity->anim_index >= current->size)
			entity->anim_index = 0;
		entity->anim_clock = current->interval;
	}
}


