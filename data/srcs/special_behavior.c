/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_behavior.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:49:59 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 13:48:50 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exchange_item(t_data *data, int item_index, t_entity *giver,
			t_entity *receiver);

void	become_merchant(void *data_param, void *entity_param)
{
	t_data		*data;
	t_entity	*entity;
	t_entity	*merchant;

	data = data_param;
	entity = entity_param;
	if (!entity)
		return ;
	if (entity->visible && entity->sheet.hp < entity->sheet.max_hp)
	{
		entity->visible = false;
		merchant = spawn_entity(data, get_prefab(data, "merchant"),
				entity->pos, ft_strdup("SOMEONE IS MAD"));
		if (merchant)
		{
			merchant->sheet.default_team = 2;
			merchant->sheet.team = 2;
			merchant->sheet.wander_ia = base_aggro;
			merchant->sheet.fight_ia = martial_ia;
			add_active(data, merchant, merchant->sheet.wander_ia);
		}
		destroy_entity(data, entity);
	}
}

void	talk_join_party(void *data_param, void *entity_param)
{
	t_data		*data;
	t_entity	*entity;

	data = data_param;
	entity = entity_param;
	if (!entity)
		return ;
	if (entity->sheet.alive && entity->dialog.dialog_i
		>= entity->dialog.dialog_size - 1)
	{
		join_party(data, entity);
		entity->behavior.func = NULL;
	}
}

int	get_inventory_name_i(t_entity **inventory, char *name)
{
	int	i;

	if (!inventory)
		return (-1);
	i = 0;
	while (i < INVENTORY_SIZE)
	{
		if (inventory[i] && !ft_strcmp(inventory[i]->sheet.name, name))
			return (i);
		i++;
	}
	return (-1);
}

void	king_reward(void *data_param, void *entity_param)
{
	t_data		*data;
	t_entity	*entity;
	int			i;

	data = data_param;
	entity = entity_param;
	if (!entity)
		return ;
	if (entity->sheet.alive && entity->dialog.dialog_i
		>= entity->dialog.dialog_size - 1)
	{
		leave_party(data, in_party_name(data, "Gobelin princess"));
		i = get_inventory_name_i(entity->sheet.inventory, "dungeon key");
		if (i == -1 || !data->player.possession)
			return ;
		exchange_item(data, i, entity, data->player.possession);
	}
}

void	king_talk(void *data_param, void *entity_param)
{
	t_data		*data;
	t_entity	*entity;

	data = data_param;
	entity = entity_param;
	if (!entity)
		return ;
	if (in_party_name(data, "Gobelin princess"))
	{
		set_entity_dialog(entity, "You did it!\\\
		You brought her back!\\\
		I cannot thank you enought for what you did stranger\\\
		Here is your reward as promised before\\\
		But always remember what happened on 1989...");
		entity->behavior.func = king_reward;
		return ;
	}
}
