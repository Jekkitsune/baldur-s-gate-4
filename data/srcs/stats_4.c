/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:08:18 by fparis            #+#    #+#             */
/*   Updated: 2025/01/27 01:02:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_specifics_buttons(t_data *data, t_entity *entity)
{
	t_button	*button;

	button = get_button_pointer(entity->sheet.buttons, "Eldritch blast");
	if (button)
		init_eldritch_blast_button(data, button);
	button = get_button_pointer(entity->sheet.buttons, "Fire bolt");
	if (button)
		init_fire_bolt_button(data, button);
	button = get_button_pointer(entity->sheet.buttons, "Healing word");
	if (button)
		init_healing_word_button(data, button);
}

char	*stat_to_str(int stat)
{
	if (stat == STR)
		return ("STR");
	if (stat == DEX)
		return ("DEX");
	if (stat == CON)
		return ("CON");
	if (stat == INT)
		return ("INT");
	if (stat == WIS)
		return ("WIS");
	if (stat == CHA)
		return ("CHA");
	return (NULL);
}
