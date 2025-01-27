/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 04:51:18 by fparis            #+#    #+#             */
/*   Updated: 2025/01/27 04:52:42 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	join_party(t_data *data, t_entity *entity)
{
	if (!entity)
		return ;
	possess_control(entity, true);
	ft_lstadd_front(&data->round_manager.party, ft_lstnew(entity));
}
