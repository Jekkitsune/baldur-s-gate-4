/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_fight_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:28:38 by fparis            #+#    #+#             */
/*   Updated: 2025/01/31 00:27:58 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	can_aggro(t_entity *entity, t_entity *current)
{
	return (current && current->sheet.alive && current->sheet.team
		!= entity->sheet.team && get_dist(entity->pos, current->pos) < 7
		&& !(current->sheet.properties & invisible)
		&& (!(entity->sheet.properties & blinded)
			|| (entity->sheet.properties & true_sight))
		&& !(entity->sheet.properties & (hypnotized)));
}
