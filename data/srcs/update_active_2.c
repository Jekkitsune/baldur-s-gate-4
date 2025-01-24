/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_active_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:37:46 by fparis            #+#    #+#             */
/*   Updated: 2025/01/24 08:43:13 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_spelltype_filter_color(t_data *data, t_entity *entity)
{
	if (!data->player.active_button)
		return ;
	if (data->player.active_button->spellinfo.type == offensive
		|| data->player.active_button->spellinfo.type == debuff)
		entity_filter(entity, 0xFFAA0000);
	else if (data->player.active_button->spellinfo.type == heal
		|| data->player.active_button->spellinfo.type == buff)
		entity_filter(entity, 0xFF00AA00);
	else
		entity_filter(entity, 0xFF888888);
}
