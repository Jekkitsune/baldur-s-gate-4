/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spells.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:49:41 by fparis            #+#    #+#             */
/*   Updated: 2025/01/06 08:37:10 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_cell(t_data *data, t_cell cell, t_spellinfo spell, void (*effect)(void *data, t_entity *target, t_entity *caster, int nb))
{
	t_list	*lst;

	lst = cell.entities;
	while (lst)
	{
		if (lst->content && ((t_entity *)lst->content)->sheet.alive)
			effect(data, lst->content, spell.caster, spell.nb);
		lst = lst->next;
	}
}

void	zone_effect(t_data *data, t_spellinfo spell, void (*effect)(void *data, t_entity *target, t_entity *caster, int nb))
{
	int	i;
	int	i2;
	int	line_size;

	i = 0;
	while (i < spell.radius + 1)
	{
		i2 = spell.pos.x - (spell.radius - i);
		while (i2 < spell.pos.x + (spell.radius - i))
		{
			if (in_bound(data->current_map, vec(i2, spell.pos.y + i)))
				apply_cell(data, data->current_map->arr[i2][spell.pos.y + i], spell, effect);
			if (i != 0 && in_bound(data->current_map, vec(i2, spell.pos.y - i)))
				apply_cell(data, data->current_map->arr[i2][spell.pos.y - i], spell, effect);
			i2++;
		}
		i++;
	}
}

void	damage(t_data *data, t_entity *entity, int dmg)
{
	t_timer_property	*prop;

	if (!entity->sheet.alive)
		return ;
	if (dmg < 0)
		dmg = 0;
	entity->sheet.hp -= dmg;
	show_info(data, "%s took %d damage\n", entity->sheet.name, dmg);
	prop = new_timer_property(hit_effect, entity);
	add_timer_property(data, prop, 0.3, false);
	if (entity->sheet.hp <= 0)
	{
		change_anim(entity, "dead", false);
		entity->sheet.alive = false;
		entity->behavior.func = death;
	}
}

t_entity	*browse_entity_cell(t_list *lst, int index, int size, t_entity *arrow)
{
	t_list			*tmp;

	tmp = lst;
	while (lst && index > 0)
	{
		lst = lst->next;
		index--;
	}
	if (!lst)
		return (NULL);
	if (lst->content == arrow)
		return (NULL);
	return (lst->content);
}

t_entity	*cycle_entity_cell(t_data *data, int move)
{
	static int		index = 0;
	static t_cell	*cell = NULL;
	t_vector		pos;
	int				size;

	if (!data->player.arrow)
		return (NULL);
	pos = data->player.arrow->pos;
	if (!in_bound(data->current_map, pos))
		return (NULL);
	size = ft_lstsize(data->current_map->arr[pos.x][pos.y].entities);
	if (!size)
		return (NULL);
	if (&data->current_map->arr[pos.x][pos.y] != cell)
	{
		cell = &data->current_map->arr[pos.x][pos.y];
		index = 0;
	}
	index += move;
	while (index >= size)
		index -= size;
	while (index < 0)
		index += size;
	return (browse_entity_cell(data->current_map->arr[pos.x][pos.y].entities,
		index, size, data->player.arrow));
}
