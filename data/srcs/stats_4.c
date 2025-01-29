/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:08:18 by fparis            #+#    #+#             */
/*   Updated: 2025/01/29 12:06:07 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_more_spec_buttons(t_data *data, t_button *button)
{
	if (!ft_strcmp(button->name, "Stunning strike"))
		init_stunning_strike_button(data, button);
	else if (!ft_strcmp(button->name, "Arrow rain"))
		init_arrow_rain_button(data, button);
}

void	update_specifics_buttons(t_data *data, t_entity *entity)
{
	t_button	*button;
	int			i;

	i = 0;
	while (i < NB_BUTTON)
	{
		button = &entity->sheet.buttons[i];
		if (!ft_strcmp(button->name, "Eldritch blast"))
			init_eldritch_blast_button(data, button);
		else if (!ft_strcmp(button->name, "Fire bolt"))
			init_fire_bolt_button(data, button);
		else if (!ft_strcmp(button->name, "Healing word"))
			init_healing_word_button(data, button);
		else if (!ft_strcmp(button->name, "Sneak attack"))
			init_sneak_atk_button(data, button);
		else if (!ft_strcmp(button->name, "Punch bonus"))
			init_bonus_punch_button(data, button);
		else if (!ft_strcmp(button->name, "Flurry of blows"))
			init_flurry_button(data, button);
		else if (!ft_strcmp(button->name, "Healing hands"))
			init_healing_hands_button(data, button);
		else
			update_more_spec_buttons(data, button);
		i++;
	}
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
