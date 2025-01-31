/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:24:26 by fparis            #+#    #+#             */
/*   Updated: 2025/01/30 22:34:17 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	round_refresh_stat(t_entity *entity)
{
	if (!entity)
		return ;
	entity->sheet.action = 1;
	entity->sheet.attack_left = 0;
	entity->sheet.bonus_action = 1;
	entity->sheet.reaction = 1;
	entity->sheet.walked = entity->sheet.speed;
	if (entity->sheet.properties & (banished | paralyzed | hypnotized
			| stunned))
	{
		entity->sheet.walked = 0;
		entity->sheet.action = 0;
		entity->sheet.bonus_action = 0;
	}
}

void	copy_stat_tab(int *stats1, int *stats2, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		stats1[i] = stats2[i];
		i++;
	}
}

void	sum_stat_tab(int *stats1, int *stats2, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		stats1[i] += stats2[i];
		i++;
	}
}

int	modif(int nb)
{
	float	res;

	res = ((float)nb - 10.0) / 2;
	if (res < 0)
		return ((int)(res - 0.5));
	return ((int)res);
}

void	set_save_pb(t_entity *entity)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (entity->sheet.saving[i])
			entity->sheet.saving[i] += entity->sheet.pb;
		entity->sheet.saving[i] += modif(entity->sheet.stats[i]);
		i++;
	}
	entity->sheet.ac += modif(entity->sheet.stats[DEX]);
	entity->sheet.atk_bonus += entity->sheet.pb;
}
