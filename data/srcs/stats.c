/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:28:28 by fparis            #+#    #+#             */
/*   Updated: 2025/01/04 06:20:55 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	modif(int nb)
{
	float	res;

	res = ((float)nb - 10.0) / 2;
	if (res < 0)
		return ((int)res - 1);
	return ((int)res);
}

void	refresh_stat(t_entity *entity)
{
	if (entity)
		return ;
	
}
