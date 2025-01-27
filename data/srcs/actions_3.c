/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 08:36:34 by fparis            #+#    #+#             */
/*   Updated: 2025/01/25 09:55:24 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_active_button(t_data *data)
{
	if (!data->player.active_button)
		return ;
	data->player.active_button->spellinfo.caster = NULL;
	data->player.active_button->spellinfo.target = NULL;
}
