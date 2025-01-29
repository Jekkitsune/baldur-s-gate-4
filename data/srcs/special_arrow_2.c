/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_arrow_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 21:41:38 by fparis            #+#    #+#             */
/*   Updated: 2025/01/28 22:24:16 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_infused_hit(t_data *data, t_spellinfo *spell)
{
	t_timer_property	*time_prop;

	if (spell->caster->sheet.properties & infused_acid)
	{
		time_prop = new_timer_property(acid, spell->target, NULL, NULL);
		add_timer_property(data, time_prop, 2, true);
	}
	if (spell->caster->sheet.properties & infused_restrained)
	{
		time_prop = new_timer_property(restrained, spell->target, NULL, NULL);
		add_timer_property(data, time_prop, 2, true);
	}
	if (spell->caster->sheet.properties & infused_silenced)
	{
		time_prop = new_timer_property(silenced, spell->target, NULL, NULL);
		add_timer_property(data, time_prop, 2, true);
	}
}
