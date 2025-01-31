/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_draw_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 21:43:55 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 21:44:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_description(t_data *data, t_entity *inventory[INVENTORY_SIZE],
	int index, t_vector pos)
{
	t_strput	*to_put;

	if (data->player.description_mode && inventory[index]->sheet.description)
	{
		pos.y -= 10;
		to_put = strput(ft_strdup(inventory[index]->sheet.description),
				pos, 20, 0xFFFFFFFF);
		to_put->bg = 0x99000000;
		to_put->left = true;
		screen_string_put(data, to_put, 0);
	}
}
