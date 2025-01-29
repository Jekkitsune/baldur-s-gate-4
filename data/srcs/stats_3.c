/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 03:53:16 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 13:40:19 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_specifics_buttons(t_data *data, t_entity *entity);

void	long_rest(t_data *data, t_entity *entity)
{
	t_entity	*prefab;
	t_class		*class;
	int			i_level;

	prefab = entity->sheet.prefab;
	class = entity->sheet.class;
	refresh_stats(data, entity);
	round_refresh_stat(entity);
	if (!prefab)
		return ;
	copy_stat_tab(entity->sheet.spell_slot, prefab->sheet.spell_slot, SPELL_MAX_LV);
	if (entity->sheet.type == living)
		entity->sheet.alive = true;
	entity->sheet.hp = entity->sheet.max_hp;
	if (!entity->sheet.class)
		return ;
	i_level = 0;
	while (i_level < entity->sheet.level && i_level < MAX_LEVEL)
	{
		sum_stat_tab(entity->sheet.spell_slot,
			class->level[i_level].add_spell_slot, SPELL_MAX_LV);
		i_level++;
	}
}

void	copy_items_buttons(t_entity *entity, int *button_nb)
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
			i2 = 0;
			while (i2 < NB_BUTTON)
			{
				if (*button_nb < NB_BUTTON - 1
					&& current->sheet.buttons[i2].func)
					entity->sheet.buttons[(*button_nb)++]
						= current->sheet.buttons[i2];
				i2++;
			}
		}
	}
}

void	copy_class_buttons(t_entity *entity, int level, int *button_nb)
{
	int		i_level;
	int		i;
	t_class	*class;

	class = entity->sheet.class;
	if (!class)
		return ;
	i_level = 0;
	while (i_level < level && i_level < MAX_LEVEL)
	{
		i = 0;
		while (*button_nb < NB_BUTTON - 1 && i < LEVEL_NB_BUTTON)
		{
			if (class->level[i_level].buttons[i].func)
			{
				entity->sheet.buttons[*button_nb] = \
				class->level[i_level].buttons[i];
				*button_nb += 1;
			}
			i++;
		}
		i_level++;
	}
}

void	copy_prefab_buttons(t_entity *entity, int *button_nb)
{
	t_entity	*prefab;
	int			i;

	prefab = entity->sheet.prefab;
	if (!prefab)
		return ;
	i = 0;
	while (i < NB_BUTTON)
	{
		ft_bzero(&entity->sheet.buttons[i], sizeof(t_button));
		i++;
	}
	i = -1;
	while (++i < NB_BUTTON && *button_nb < NB_BUTTON - 1)
	{
		if (prefab->sheet.buttons[i].func)
			entity->sheet.buttons[(*button_nb)++] = prefab->sheet.buttons[i];
	}
}

void	init_all_buttons(t_data *data, t_entity *entity)
{
	int	button_nb;
	int	i;

	button_nb = 0;
	copy_prefab_buttons(entity, &button_nb);
	if (button_nb < NB_BUTTON - 1)
		init_check_button(data, &entity->sheet.buttons[button_nb++]);
	if (button_nb < NB_BUTTON - 1)
		init_move_button(data, &entity->sheet.buttons[button_nb++]);
	if (button_nb < NB_BUTTON - 1)
		init_dash_button(data, &entity->sheet.buttons[button_nb++]);
	if (button_nb < NB_BUTTON - 1)
		init_interact_button(data, &entity->sheet.buttons[button_nb++]);
	if (button_nb < NB_BUTTON - 1)
		init_atk_button(data, &entity->sheet.buttons[button_nb++], entity);
	copy_class_buttons(entity, entity->sheet.level, &button_nb);
	copy_items_buttons(entity, &button_nb);
	init_inventory_button(data, &entity->sheet.buttons[NB_BUTTON - 1]);
	i = 0;
	while (i < NB_BUTTON)
	{
		entity->sheet.buttons[i].user = entity;
		i++;
	}
	update_specifics_buttons(data, entity);
}
