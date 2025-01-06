/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:28:28 by fparis            #+#    #+#             */
/*   Updated: 2025/01/06 03:16:00 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_stat_tab(int stats1[6], int stats2[6])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		stats1[i] = stats2[i];
		i++;
	}
}

void	sum_stat_tab(int stats1[6], int stats2[6])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		stats1[i] += stats2[i];
		i++;
	}
}

int	modif(int nb)
{
	float	res;

	res = ((float)nb - 10.0) / 2;
	if (res < 0)
		return ((int)res - 1);
	return ((int)res);
}

void	reset_stats(t_data *data, t_entity *entity, t_entity *prefab, int *button_nb)
{
	int	i;

	i = 0;
	while (i < NB_BUTTON)
		ft_bzero(&entity->sheet.buttons[i++], sizeof(t_button));
	i = 0;
	while (i < NB_BUTTON && *button_nb < NB_BUTTON - 1)
	{
		if (prefab->sheet.buttons[i].func)
			entity->sheet.buttons[(*button_nb)++] = prefab->sheet.buttons[i];
		i++;
	}
	entity->sheet.max_hp = prefab->sheet.max_hp;
	entity->sheet.pb = prefab->sheet.pb;
	entity->sheet.ac = prefab->sheet.ac;
	entity->sheet.atk_bonus = prefab->sheet.atk_bonus;
	entity->sheet.weight = prefab->sheet.weight;
	entity->sheet.carry = prefab->sheet.carry;
	entity->sheet.spell_bonus = prefab->sheet.spell_bonus;
	entity->sheet.spell_dc = prefab->sheet.spell_dc;
	entity->sheet.speed = prefab->sheet.speed;
	entity->sheet.properties = prefab->sheet.properties;
	copy_stat_tab(entity->sheet.stats, prefab->sheet.stats);
	copy_stat_tab(entity->sheet.saving, prefab->sheet.saving);
}

void	add_stat(t_data *data, t_entity *entity, t_entity *item)
{
	entity->sheet.max_hp += item->sheet.max_hp;
	entity->sheet.pb += item->sheet.pb;
	entity->sheet.ac += item->sheet.ac;
	entity->sheet.atk_bonus += item->sheet.atk_bonus;
	entity->sheet.weight += item->sheet.weight;
	entity->sheet.carry += item->sheet.carry;
	entity->sheet.spell_bonus += item->sheet.spell_bonus;
	entity->sheet.spell_dc += item->sheet.spell_dc;
	entity->sheet.speed += item->sheet.speed;
	entity->sheet.properties |= item->sheet.properties;
	sum_stat_tab(entity->sheet.stats, item->sheet.stats);
	sum_stat_tab(entity->sheet.saving, item->sheet.saving);
}

void	add_weight(t_entity *entity)
{
	int			i;
	t_entity	*current;

	i = NON_EQUIP;
	while (i < INVENTORY_SIZE)
	{
		current = entity->sheet.inventory[i++]; 
		if (current)
			entity->sheet.weight += current->sheet.weight;
	}
}

void	check_inventory_stats(t_data *data, t_entity *entity, int *button_nb)
{
	int			i;
	int			i2;
	t_entity	*current;

	i = 0;
	while (i < NON_EQUIP)
	{
		current = entity->sheet.inventory[i++]; 
		if (current)
		{
			while (i2 < NB_BUTTON)
			i2 = 0;
			{
				if (*button_nb < NB_BUTTON - 1 && current->sheet.buttons[i2].func)
					entity->sheet.buttons[(*button_nb)++] = current->sheet.buttons[i2++];
				add_stat(data, entity, current);
			}
		}
	}
	add_weight(entity);
}

void	set_save_pb(t_entity *entity)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (entity->sheet.saving[i])
			entity->sheet.saving[i] += entity->sheet.pb;
		i++;
	}
}

void	refresh_stats(t_data *data, t_entity *entity)
{
	t_entity	*prefab;
	int			button_nb;

	if (!entity || !entity->sheet.prefab)
		return ;
	prefab = get_prefab(data, entity->sheet.prefab);
	if (!prefab)
		return ;
	button_nb = 0;
	reset_stats(data, entity, prefab, &button_nb);
	if (button_nb < NB_BUTTON - 1)
		init_check_button(data, &entity->sheet.buttons[button_nb++]);
	if (button_nb < NB_BUTTON - 1)
		init_move_button(data, &entity->sheet.buttons[button_nb++]);
	if (button_nb < NB_BUTTON - 1)
		init_take_button(data, &entity->sheet.buttons[button_nb++]);
	if (button_nb < NB_BUTTON - 1)
		init_atk_button(data, &entity->sheet.buttons[button_nb++], entity);
	refresh_entity_class(entity, entity->sheet.level, &button_nb);
	init_inventory_button(data, &entity->sheet.buttons[NB_BUTTON - 1]);
	set_save_pb(entity);
	check_inventory_stats(data, entity, &button_nb);
	set_all_entity_timer_prop(data, entity);
}
