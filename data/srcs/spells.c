/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spells.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:49:41 by fparis            #+#    #+#             */
/*   Updated: 2024/12/16 21:09:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spell_info(t_spellinfo *spell, void (*effect)(void *data, t_entity *target, t_entity *caster, int nb),
	t_vector pos, t_entity *caster)
{
	spell->nb = 0;
	spell->effect = effect;
	spell->pos = pos;
	spell->caster = caster;
}

void	apply_cell(t_data *data, t_cell cell, t_spellinfo spell)
{
	t_list	*lst;

	lst = cell.entities;
	while (lst)
	{
		spell.effect(data, lst->content, spell.caster, spell.nb);
		lst = lst->next;
	}
}

void	zone_effect(t_data *data, t_spellinfo spell)
{
	int	i;
	int	i2;
	int	line_size;

	i = 0;
	while (i < spell.radius + 1)
	{
		i2 = spell.pos.x - (spell.radius - i);
		printf("%d\n", i2);
		while (i2 < spell.pos.x + (spell.radius - i))
		{
			if (in_bound(*data->current_map, vec(i2, spell.pos.y + i)))
				apply_cell(data, data->current_map->arr[i2][spell.pos.y + i], spell);
			if (i != 0 && in_bound(*data->current_map, vec(i2, spell.pos.y - i)))
				apply_cell(data, data->current_map->arr[i2][spell.pos.y - i], spell);
			i2++;
		}
		i++;
	}
}

void	damage(t_data *data, t_entity *entity, int dmg)
{
	if (entity->sheet.hp <= 0)
		return ;
	entity->sheet.hp -= dmg;
	printf("%s took %d damage\n", entity->sheet.name, dmg);
	if (entity->sheet.hp <= 0)
	{
		change_anim(entity, "dead");
		entity->sheet.alive = false;
		entity->behavior = death;
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
	if (!in_bound(*data->current_map, pos))
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
