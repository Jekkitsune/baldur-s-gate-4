/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dice_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:13:42 by fparis            #+#    #+#             */
/*   Updated: 2025/01/15 20:14:03 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_dice_average(t_dice dice)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (i < NB_DICE)
	{
		res += (dice[i] * index_dice(i) + dice[i]) / 2;
		i++;
	}
	return (res);
}

t_bool	has_dice(t_dice dice)
{
	int	i;

	i = 0;
	while (i < NB_DICE)
	{
		if (dice[i++])
			return (true);
	}
	return (false);
}

int	dice_i(int dice)
{
	if (dice == 1)
		return (D1);
	if (dice == 4)
		return (D4);
	if (dice == 6)
		return (D6);
	if (dice == 8)
		return (D8);
	if (dice == 10)
		return (D10);
	if (dice == 12)
		return (D12);
	if (dice == 20)
		return (D20);
	if (dice == 100)
		return (D100);
	return (-1);
}

int	index_dice(int i)
{
	if (i == D1)
		return (1);
	if (i == D4)
		return (4);
	if (i == D6)
		return (6);
	if (i == D8)
		return (8);
	if (i == D10)
		return (10);
	if (i == D12)
		return (12);
	if (i == D20)
		return (20);
	if (i == D100)
		return (100);
	return (-1);
}
